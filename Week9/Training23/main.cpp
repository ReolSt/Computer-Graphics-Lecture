#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include <reactphysics3d/reactphysics3d.h>

#include "../GL/GL.h"

void ToggleSpeed(float& speed, float targetSpeed)
{
	if (speed == targetSpeed)
	{
		speed = 0.0f;
	}
	else
	{
		speed = targetSpeed;
	}
}

void OffSpeed(float& speed, float targetSpeed)
{
	if (speed == targetSpeed)
	{
		speed = 0.0f;
	}
}

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController, float fov = 90.0f, float left = -5.0f, float right = 5.0f, float bottom = -5.0f, float top = 5.0f)
		: GSuperClassInitializer(GLGameObject), Fov(fov), Left(left), Right(right), Bottom(bottom), Top(top) { }

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Perspective = GCreateChild(GPerspectiveCamera, this->Fov);
		this->Orthographic = GCreateChild(GOrthographicCamera, this->Left, this->Right, this->Bottom, this->Top);

		this->AddChildren({ this->Perspective, this->Orthographic });
		this->Scene->AddCamera(this->Perspective);
		this->Scene->AddCamera(this->Orthographic);

		this->Activate();
	}

	void SetOrder(int order)
	{
		this->Perspective->SetOrder(order);
		this->Orthographic->SetOrder(order);
	}

	int GetOrder()
	{
		return this->Perspective->GetOrder();
	}

	void Activate()
	{
		this->Activated = true;

		this->Perspective->SetActive(this->State == 0);
		this->Orthographic->SetActive(this->State == 1);
	}

	void Deactivate()
	{
		this->Activated = false;

		this->Perspective->SetActive(false);
		this->Orthographic->SetActive(false);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GCameraController::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "p")
		{
			this->State = 0;
		}
		else if (key == "o")
		{
			this->State = 1;
		}

		if (this->Activated)
		{
			this->Activate();
		}
	}

	GLSharedPtr<GPerspectiveCamera> Perspective;
	GLSharedPtr<GOrthographicCamera> Orthographic;

	int State = 0;
	int Activated = true;

protected:
	float Fov;
	float Left;
	float Right;
	float Bottom;
	float Top;
};

class GPhysicsObject : public GLGameObject
{
public:
	GConstructor(GPhysicsObject)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
	}

	virtual ~GPhysicsObject()
	{
		this->Scene->Physics->DestroyRigidBody(this->RigidBody);
	}

	void Translate(float x, float y, float z)
	{
		auto physicsTransform = this->Scene->Physics->GetPhysicsTransform(this->Transform);

		auto position = physicsTransform.getPosition();
		position.x += x;
		position.y += y;
		position.z += z;

		physicsTransform.setPosition(position);

		this->RigidBody->setTransform(physicsTransform);
		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	void SetRotation(float x, float y, float z, float w)
	{
		auto physicsTransform = this->Scene->Physics->GetPhysicsTransform(this->Transform);

		physicsTransform.setOrientation(reactphysics3d::Quaternion(x, y, z, w));

		this->RigidBody->setTransform(physicsTransform);
		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		if (this->Scene)
		{
			this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
		}
	}

	reactphysics3d::RigidBody* RigidBody = nullptr;
};

class GPhysicsRectangle : public GPhysicsObject
{
public:
	GConstructor(GPhysicsRectangle)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		this->MeshRenderer->Mesh = GLCreate<GLRectangleMesh>();
		auto scale = this->Transform->GetScale();

		this->CollisionShape = this->Scene->Physics->CreateBoxShape(glm::vec3(scale.x / 2, scale.y / 2, 0.2f));

		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	reactphysics3d::BoxShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;
};

class GPhysicsCube : public GPhysicsObject
{
public:
	GConstructor(GPhysicsCube)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		this->MeshRenderer->Mesh = GLCreate<GLCubeMesh>();
		auto scale = this->Transform->GetScale();

		this->CollisionShape = this->Scene->Physics->CreateBoxShape(scale / 2.0f);

		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	reactphysics3d::BoxShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;
};

class GPhysicsSphere : public GPhysicsObject
{
public:
	GConstructor(GPhysicsSphere)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		this->MeshRenderer->Mesh = GLCreate<GLUVSphereMesh>();

		auto scale = this->Transform->GetScale();

		float height = scale.y / 2.0f;
		float radius = (scale.x + scale.z) / 8.0f;

		this->CollisionShape = this->Scene->Physics->CreateCapsuleShape(radius, height);

		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	reactphysics3d::CapsuleShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;
};

class GBall : public GPhysicsSphere
{
public:
	GConstructor(GBall)
		: GSuperClassInitializer(GPhysicsSphere)
	{ }

	void Initialize() override
	{
		GPhysicsSphere::Initialize();

		this->RigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
		this->RigidBody->enableGravity(false);
		this->RigidBody->setMass(0.001f);

		this->RigidBody->setLinearVelocity(reactphysics3d::Vector3(Rand(1.5f, 3.0f), Rand(1.5f, 3.0f), 0.0f));
		SetVertexColor(this->MeshRenderer->Mesh, RandColor3f());

		auto& material = this->Collider->getMaterial();
		material.setBounciness(1.0f);
	}

	void Update(float deltaTime) override
	{
		GPhysicsSphere::Update(deltaTime);
	}

};

class GMainArea : public GLGameObject
{
public:
	GConstructor(GMainArea)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize()
	{
		this->Left = GCreate(GPhysicsRectangle);
		this->Right = GCreate(GPhysicsRectangle);
		this->Bottom = GCreate(GLGameObject);
		this->Top = GCreate(GPhysicsRectangle);
		this->Back = GCreate(GPhysicsRectangle);
		this->Front = GCreate(GPhysicsRectangle);

		this->BottomMeshObject = GCreate(GPhysicsRectangle);

		this->Left->Transform->Translate(-0.5f, 0.0f, 0.0f);
		this->Left->Transform->Rotate(0.0f, glm::radians(-90.0f), 0.0f);

		this->Right->Transform->Translate(0.5f, 0.0f, 0.0f);
		this->Right->Transform->Rotate(0.0f, glm::radians(90.0f), 0.0f);
		
		this->Bottom->Transform->Translate(0.0f, -0.5f, -0.5f);
		this->Bottom->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		this->BottomMeshObject->Transform->Translate(0.0f, 0.5f, 0.0f);

		this->Top->Transform->Translate(0.0f, 0.5f, 0.0f);
		this->Top->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->Back->Transform->Translate(0.0f, 0.0f, -0.5f);
		this->Front->Transform->Translate(0.0f, 0.0f, 0.5f);

		this->AddChildren({ this->Left, this->Right, this->Bottom, this->Top, this->Back, this->Front });
		this->Bottom->AddChild(this->BottomMeshObject);

		this->Transform->SetScale(5.0f, 5.0f, 5.0f);
		this->Transform->Rotate(0.0f, 0.0f, glm::radians(45.0f));

		this->Left->Initialize();
		this->Right->Initialize();
		this->Bottom->Initialize();
		this->Top->Initialize();
		this->Back->Initialize();
		this->Front->Initialize();

		this->BottomMeshObject->Initialize();

		SetVertexColor(this->Left, GLColor(1.0f, 0.0f, 1.0f));
		SetVertexColor(this->Right, GLColor(0.5f, 0.0f, 1.0f));
		SetVertexColor(this->BottomMeshObject, GLColor(0.2f, 0.2f, 0.2f));
		SetVertexColor(this->Top, GLColor(0.0f, 0.2f, 0.8f));
		SetVertexColor(this->Back, GLColor(0.7f, 0.7f, 0.7f));
		SetVertexColor(this->Front, GLColor(1.0f, 1.0f, 1.0f, 1.0f));

		this->Front->SetVisible(false);

		this->CreateBalls();
		this->CreateCubes();		
	}

	void CreateBalls()
	{
		for (const auto& ball : this->Balls)
		{
			this->RemoveChild(ball);
		}

		this->Balls.clear();
		for (auto i = 0; i < 5; ++i)
		{
			auto ball = GCreate(GBall);
			ball->Transform->SetScale(0.1f, 0.1f, 0.1f);
			ball->Transform->Translate(Rand(-0.3f, 0.3f), Rand(-0.3f, 0.3f), Rand(-0.3f, 0.3f));
			this->AddChild(ball);

			ball->Initialize();
			this->Balls.push_back(ball);
		}
	}

	void CreateCubes()
	{
		for (const auto& cube : this->Cubes)
		{
			this->RemoveChild(cube);
		}

		this->Cubes.clear();
		for (auto i = 0; i < 3; ++i)
		{
			auto cube = GCreate(GPhysicsCube);

			float size = (i + 1) * 0.1f;
			cube->Transform->SetScale(size, size, size);
			cube->Transform->Translate(0.0f, 0.0f, 0.5f - (i + 1) * 0.25f);

			this->AddChild(cube);

			cube->Initialize();

			RandVertexColor3f(cube);
			cube->RigidBody->setType(reactphysics3d::BodyType::DYNAMIC);

			this->Cubes.push_back(cube);
		}
	}

	void UpdateRigidBody()
	{
		this->Scene->Physics->UpdateRigidBodyRotation(this->Left->RigidBody, this->Left->Transform);
		this->Scene->Physics->UpdateRigidBodyRotation(this->Right->RigidBody, this->Right->Transform);
		this->Scene->Physics->UpdateRigidBodyRotation(this->BottomMeshObject->RigidBody, this->BottomMeshObject->Transform);
		this->Scene->Physics->UpdateRigidBodyRotation(this->Top->RigidBody, this->Top->Transform);
		this->Scene->Physics->UpdateRigidBodyRotation(this->Back->RigidBody, this->Back->Transform);
		this->Scene->Physics->UpdateRigidBodyRotation(this->Front->RigidBody, this->Front->Transform);
	}

	void OnMouseMove(int button, int x, int y) override
	{
		static int px = x;
		static int py = y;

		if (button == 0)
		{
			int dx = x - px;
			int dy = y - py;

			this->Transform->Rotate(0.0f, 0.0f, dx / 50.0f);
			UpdateRigidBody();
		}

		px = x;
		py = y;
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "Enter")
		{
			this->OpenTransition = true;
		}
		if (key == "b" || key == "B")
		{
			this->CreateBalls();
		}
		if (key == "c" || key == "C")
		{
			this->CreateCubes();
			this->CreateBalls();

			this->Transform->SetLocalEulerAngles(0.0f, 0.0f, glm::radians(45.0f));
			this->Bottom->Transform->SetLocalEulerAngles(glm::radians(90.0f), 0.0f, 0.0f);
			this->OpenTransition = false;
			this->OpenTransitionAmount = 0.0f;

			this->UpdateRigidBody();
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		if (this->OpenTransition)
		{
			this->Bottom->Transform->Rotate(deltaTime * this->OpenTransitionSpeed, 0.0f, 0.0f);
			this->UpdateRigidBody();

			this->OpenTransitionAmount += deltaTime * this->OpenTransitionSpeed;

			if (this->OpenTransitionAmount >= glm::radians(90.0f))
			{
				this->OpenTransition = false;
			}
		}
	}

	GLSharedPtr<GPhysicsRectangle> Left;
	GLSharedPtr<GPhysicsRectangle> Right;
	GLSharedPtr<GLGameObject> Bottom;
	GLSharedPtr<GPhysicsRectangle> BottomMeshObject;
	GLSharedPtr<GPhysicsRectangle> Top;
	GLSharedPtr<GPhysicsRectangle> Back;
	GLSharedPtr<GPhysicsRectangle> Front;

	std::vector<GLSharedPtr<GPhysicsSphere>> Balls;
	std::vector<GLSharedPtr<GPhysicsCube>> Cubes;

	float OpenTransitionAmount = 0.0f;
	float OpenTransitionSpeed = 1.0f;
	bool OpenTransition = false;
};

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize()
	{
		this->MainArea = GCreate(GMainArea);

		this->MainCamera = GCreate(GCameraController, 90.0f, -8.0f, 8.0f, -8.0f, 8.0f);

		this->AddChildren({ this->MainArea, this->MainCamera });

		this->MainArea->Initialize();
		this->MainCamera->Initialize();

		this->MainCamera->Transform->Translate(0.0f, 1.0f, 7.5f);
		this->Scene->Physics->SetDebug(true);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GWorld::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "z")
		{
			this->CameraCurrentSpeed.z = 1.0f;
		}
		else if (key == "Z")
		{
			this->CameraCurrentSpeed.z = -1.0f;
		}
		else if (key == "y")
		{
			this->CameraCurrentRotationSpeed.y = 1.0f;
		}
		else if (key == "Y")
		{
			this->CameraCurrentRotationSpeed.y = -1.0f;
		}
		else if (key == "Tab")
		{
			if (this->Scene->Physics->GetDebug())
			{
				this->Scene->Physics->SetDebug(false);
			}
			else
			{
				this->Scene->Physics->SetDebug(true);
			}
		}
		if (key == "q" || key == "Q")
		{
			glutLeaveMainLoop();
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "z")
		{
			OffSpeed(this->CameraCurrentSpeed.z, 1.0f);
		}
		else if (key == "Z")
		{
			OffSpeed(this->CameraCurrentSpeed.z, -1.0f);
		}
		else if (key == "y")
		{
			OffSpeed(this->CameraCurrentRotationSpeed.y, 1.0f);
		}
		else if (key == "Y")
		{
			OffSpeed(this->CameraCurrentRotationSpeed.y, -1.0f);
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->MainCamera->Transform->Translate(this->CameraCurrentSpeed * deltaTime);
		this->MainCamera->Transform->RotateAround(glm::vec3(0.0f, 0.0f, 0.0f),
			this->CameraCurrentRotationSpeed.y * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	GLSharedPtr<GMainArea> MainArea;
	GLSharedPtr<GCameraController> MainCamera;

	glm::vec3 CameraCurrentSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 CameraCurrentRotationSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training23"));

	InitializeGLEW();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto scene = GLCreate<GLScene>("Training23");
	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
	GLLoadScene(scene);

	auto World = GCreate(GWorld);
	scene->Root->AddChild(World);
	World->Initialize();

	glutMainLoop();
}