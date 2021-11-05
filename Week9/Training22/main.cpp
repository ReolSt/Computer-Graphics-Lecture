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

	virtual ~GPhysicsRectangle() { }

	void Initialize() override
	{
		this->MeshRenderer->Mesh = GLCreate<GLRectangleMesh>();
		auto scale = this->Transform->GetScale();

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(glm::vec3(scale.x / 2, scale.y / 2, 0.2f));

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);

		auto& material = collider->getMaterial();

		material.setRollingResistance(1.0f);
		material.setBounciness(0.0f);
	}

	reactphysics3d::BoxShape* CollisionShape = nullptr;
};

class GPhysicsCube : public GPhysicsObject
{
public:
	GConstructor(GPhysicsCube)
		: GSuperClassInitializer(GPhysicsObject) { }

	virtual ~GPhysicsCube() { }

	void Initialize() override
	{
		this->MeshRenderer->Mesh = GLCreate<GLCubeMesh>();
		auto scale = this->Transform->GetScale();

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(scale / 2.0f);

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);

		auto& material = collider->getMaterial();

		material.setRollingResistance(1.0f);
		material.setBounciness(0.0f);

		collider->setMaterial(material);
	}

	reactphysics3d::BoxShape* CollisionShape = nullptr;
};

class GPhysicsSphere : public GPhysicsObject
{
public:
	GConstructor(GPhysicsSphere)
		: GSuperClassInitializer(GPhysicsObject) { }

	virtual ~GPhysicsSphere() { }

	void Initialize() override
	{
		this->MeshRenderer->Mesh = GLCreate<GLUVSphereMesh>();

		auto scale = this->Transform->GetScale();

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);

		float height = scale.y;
		float radius = (scale.x + scale.z) / 4.0f;
		this->CollisionShape = this->Scene->Physics->CreateCapsuleShape(radius, height);

		this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
	}

	reactphysics3d::CapsuleShape* CollisionShape = nullptr;
};

class GRobot : public GPhysicsObject
{
public:
	GConstructor(GRobot)
		: GSuperClassInitializer(GPhysicsObject) { }

	virtual ~GRobot() { }

	void Initialize()
	{
		this->Head = GCreate(GCube);
		this->Nose = GCreate(GCube);
		this->Body = GCreate(GCube);
		this->LeftArmAxis = GCreate(GLGameObject);
		this->LeftArm = GCreate(GCube);
		this->RightArmAxis = GCreate(GLGameObject);
		this->RightArm = GCreate(GCube);
		this->LeftLegAxis = GCreate(GLGameObject);
		this->LeftLeg = GCreate(GCube);
		this->RightLegAxis = GCreate(GLGameObject);
		this->RightLeg = GCreate(GCube);

		SetVertexColor(this->Head, GLColor(1.0f, 1.0f, 0.0f));
		SetVertexColor(this->Nose, GLColor(0.5f, 0.0f, 1.0f));
		SetVertexColor(this->Body, GLColor(0.0f, 1.0f, 0.0f));
		SetVertexColor(this->LeftArm, GLColor(0.5f, 0.5f, 1.0f));
		SetVertexColor(this->RightArm, GLColor(0.5f, 0.5f, 1.0f));
		SetVertexColor(this->LeftLeg, GLColor(0.0f, 0.2f, 1.0f));
		SetVertexColor(this->RightLeg, GLColor(0.0f, 0.2f, 1.0f));

		this->Head->Transform->Translate(0.0f, 0.45f, 0.0f);
		this->Head->Transform->SetScale(0.2f, 0.25f, 0.2f);

		this->Nose->Transform->Translate(0.0f, 0.45f, 0.1125f);
		this->Nose->Transform->SetScale(0.025f, 0.05f, 0.025f);

		this->Body->Transform->Translate(0.0f, 0.1f, 0.0f);
		this->Body->Transform->SetScale(0.35f, 0.5f, 0.3f);

		this->LeftArmAxis->Transform->Translate(-0.2f, 0.35f, 0.0f);

		this->LeftArm->Transform->Translate(0.0f, -0.25f, 0.0f);
		this->LeftArm->Transform->SetScale(0.1f, 0.5f, 0.1f);

		this->RightArmAxis->Transform->Translate(0.2f, 0.35f, 0.0f);

		this->RightArm->Transform->Translate(0.0f, -0.25f, 0.0f);
		this->RightArm->Transform->SetScale(0.1f, 0.5f, 0.1f);

		this->LeftLegAxis->Transform->Translate(-0.1f, -0.2f, 0.0f);

		this->LeftLeg->Transform->Translate(0.0f, -0.15f, 0.0f);
		this->LeftLeg->Transform->SetScale(0.1f, 0.5f, 0.1f);

		this->RightLegAxis->Transform->Translate(0.1f, -0.2f, 0.0f);

		this->RightLeg->Transform->Translate(0.0f, -0.15f, 0.0f);
		this->RightLeg->Transform->SetScale(0.1f, 0.5f, 0.1f);

		this->AddChildren({
			this->Head, this->Nose, this->Body, this->LeftArmAxis, this->RightArmAxis, this->LeftLegAxis, this->RightLegAxis });

		this->LeftArmAxis->AddChild(this->LeftArm);
		this->RightArmAxis->AddChild(this->RightArm);

		this->LeftLegAxis->AddChild(this->LeftLeg);
		this->RightLegAxis->AddChild(this->RightLeg);

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateCapsuleShape(0.5f, 2.0f);

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		auto& material = collider->getMaterial();

		material.setRollingResistance(1.0f);
		material.setBounciness(0.0f);

		collider->setMaterial(material);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "w")
		{
			this->CurrentSpeed.z = -this->Speed.z;
		}
		else if (key == "a")
		{
			this->CurrentSpeed.x = -this->Speed.x;
		}
		else if (key == "s")
		{
			this->CurrentSpeed.z = this->Speed.z;
		}
		else if (key == "d")
		{
			this->CurrentSpeed.x = this->Speed.x;
		}
		else if (key == "j" || key == "J")
		{
			if (!this->IsJumping)
			{
				this->RigidBody->setLinearVelocity(reactphysics3d::Vector3(0.0f, 5.0f, 0.0f));
				this->IsJumping = true;
			}
		}

	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "w")
		{
			OffSpeed(this->CurrentSpeed.z, -this->Speed.z);
		}
		else if (key == "a")
		{
			OffSpeed(this->CurrentSpeed.x, -this->Speed.x);
		}
		else if (key == "s")
		{
			OffSpeed(this->CurrentSpeed.z, this->Speed.z);
		}
		else if (key == "d")
		{
			OffSpeed(this->CurrentSpeed.x, this->Speed.x);
		}
		else if (key == "j" || key == "J")
		{
			this->IsJumping = false;
		}
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto speed = this->CurrentSpeed * deltaTime;
		this->Translate(speed.x, speed.y, speed.z);

		if (speed.x != 0.0f || speed.y != 0.0f || speed.z != 0.0f)
		{
			if (!this->SwingDirection)
			{
				this->SwingDirection = 1;
			}			
		}
		else if(speed.x == 0.0f && speed.y == 0.0f && speed.z == 0.0f)
		{
			this->SwingDirection = 0;
			this->LeftArmAxis->Transform->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->RightArmAxis->Transform->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->LeftLegAxis->Transform->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->RightLegAxis->Transform->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->SwingAmount = 0.0f;
		}

		if(this->SwingDirection)
		{
			this->LeftArmAxis->Transform->Rotate(this->SwingDirection * this->SwingSpeed * deltaTime, 0.0f, 0.0f);
			this->RightArmAxis->Transform->Rotate(-this->SwingDirection * this->SwingSpeed * deltaTime, 0.0f, 0.0f);
			this->LeftLegAxis->Transform->Rotate(-this->SwingDirection * this->SwingSpeed * deltaTime, 0.0f, 0.0f);
			this->RightLegAxis->Transform->Rotate(this->SwingDirection * this->SwingSpeed * deltaTime, 0.0f, 0.0f);
			this->SwingAmount += this->SwingDirection * this->SwingSpeed * deltaTime;

			if (this->SwingDirection > 0 && this->SwingAmount >= glm::radians(45.0f))
			{
				this->SwingDirection = -1;
			}
			else if (this->SwingDirection < 0 && this->SwingAmount <= glm::radians(-45.0f))
			{
				this->SwingDirection = 1;
			}
		}

		if (this->CurrentSpeed.x > 0.0f)
		{
			this->Angle = glm::radians(90.0f);
		}
		else if (this->CurrentSpeed.x < 0.0f)
		{
			this->Angle = glm::radians(270.0f);
		}

		if (this->CurrentSpeed.z > 0)
		{
			if (this->Angle != 0.0f)
			{
				this->Angle = (this->Angle + glm::radians(glm::degrees(this->Angle) > 180.0f ? 360.0f : 0.0f)) / 2.0f;
			}
			else
			{
				this->Angle = 0.0f;
			}
		}
		else if (this->CurrentSpeed.z < 0)
		{
			if (this->Angle != 0.0f)
			{
				this->Angle = (this->Angle + glm::radians(180.0f)) / 2.0f;
			}
			else
			{
				this->Angle = glm::radians(180.0f);
			}
		}

		this->Transform->SetEulerAngles(0.0f, Angle, 0.0f);
		this->Scene->Physics->UpdateRigidBodyRotation(this->RigidBody, this->Transform);
	}

	GLSharedPtr<GLGameObject> Head;
	GLSharedPtr<GLGameObject> Nose;
	GLSharedPtr<GLGameObject> Body;
	GLSharedPtr<GLGameObject> LeftArmAxis;
	GLSharedPtr<GLGameObject> LeftArm;
	GLSharedPtr<GLGameObject> RightArmAxis;
	GLSharedPtr<GLGameObject> RightArm;
	GLSharedPtr<GLGameObject> LeftLegAxis;
	GLSharedPtr<GLGameObject> LeftLeg;
	GLSharedPtr<GLGameObject> RightLegAxis;
	GLSharedPtr<GLGameObject> RightLeg;
	
	reactphysics3d::CapsuleShape* CollisionShape;

	glm::vec3 CurrentSpeed = glm::vec3(0.0f);
	glm::vec3 Speed = glm::vec3(1.0f);

	float Angle = 0.0f;

	int SwingDirection = 0;
	float SwingAmount = 0.0f;
	float SwingSpeed = 3.0f;

	bool IsJumping = false;
};

class GStage : public GLGameObject
{
public:
	GConstructor(GStage)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize()
	{
		this->Left = GCreate(GPhysicsRectangle);
		this->Right = GCreate(GPhysicsRectangle);
		this->Bottom = GCreate(GPhysicsRectangle);
		this->Top = GCreate(GPhysicsRectangle);
		this->Back = GCreate(GPhysicsRectangle);
		this->Front = GCreate(GLGameObject);
		this->FrontMeshObject = GCreate(GPhysicsRectangle);

		this->Left->Transform->Translate(-0.5f, 0.0f, 0.0f);
		this->Left->Transform->Rotate(0.0f, glm::radians(-90.0f), 0.0f);

		this->Right->Transform->Translate(0.5f, 0.0f, 0.0f);
		this->Right->Transform->Rotate(0.0f, glm::radians(90.0f), 0.0f);

		this->Bottom->Transform->Translate(0.0f, -0.5f, 0.0f);
		this->Bottom->Transform->Rotate(glm::radians(-90.0f), 0.0f, 0.0f);

		this->Top->Transform->Translate(0.0f, 0.5f, 0.0f);
		this->Top->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->Back->Transform->Translate(0.0f, 0.0f, -0.5f);
		this->Front->Transform->Translate(0.0f, -0.5f, 0.5f);
		this->FrontMeshObject->Transform->Translate(0.0f, 0.5f, 0.0f);

		this->Robot = GCreate(GRobot);
		this->Robot->Transform->SetScale(0.4f, 0.4f, 0.4f);

		this->AddChildren({ this->Left, this->Right, this->Bottom, this->Top, this->Back, this->Front, this->Robot });
		this->Front->AddChild(this->FrontMeshObject);

		this->Transform->SetScale(6.0f, 6.0f, 6.0f);

		this->Left->Initialize();
		this->Right->Initialize();
		this->Bottom->Initialize();
		this->Top->Initialize();
		this->Back->Initialize();
		this->Front->Initialize();
		this->FrontMeshObject->Initialize();

		this->Robot->Initialize();

		RandVertexColor3f(this->Left);
		RandVertexColor3f(this->Right);
		RandVertexColor3f(this->Bottom);
		RandVertexColor3f(this->Top);
		RandVertexColor3f(this->Back);
		RandVertexColor3f(this->FrontMeshObject);

		for (auto i = 0; i < 3; ++i)
		{
			auto obstacle = GCreate(GPhysicsCube);

			this->Obstacles.push_back(obstacle);
			this->AddChild(obstacle);

			obstacle->Transform->SetScale(Rand(0.7f, 1.3f), 0.5f, Rand(0.7f, 1.3f));
			obstacle->Transform->Translate(Rand(-1.8f, 1.8f), -2.5f, Rand(-1.8f, 1.8f));

			obstacle->Initialize();

			RandVertexColor3f(obstacle);
			obstacle->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "i" || key == "I")
		{
			this->RemoveChild(this->Robot);

			this->Robot = GCreate(GRobot);
			this->Robot->Transform->SetScale(0.4f, 0.4f, 0.4f);
			this->AddChild(this->Robot);

			this->Front->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
			this->Scene->Physics->UpdateRigidBody(this->FrontMeshObject->RigidBody, this->FrontMeshObject->Transform);

			this->doorRotationDirection = 0;
			this->doorRotationAmount = 0.0f;

			this->Robot->Initialize();
		}
		else if (key == "o")
		{
			if (this->doorRotationDirection != 1)
			{
				this->doorRotationDirection = 1;
			}
			else
			{
				this->doorRotationDirection = 0;
			}
		}
		else if (key == "O")
		{
			if (this->doorRotationDirection != -1)
			{
				this->doorRotationDirection = -1;
			}
			else
			{
				this->doorRotationDirection = 0;
			}
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto robotPosition = this->Robot->Transform->GetPosition();

		

		if (this->Robot->RigidBody->testAABBOverlap(this->Right->RigidBody->getAABB()))
		{
			robotPosition.x = -2.2f;
		}
		else if (this->Robot->RigidBody->testAABBOverlap(this->Left->RigidBody->getAABB()))
		{
			robotPosition.x = 2.2f;
		}

		if (robotPosition.z > 2.3f)
		{
			robotPosition.z = -2.2f;
		}
		else if (this->Robot->RigidBody->testAABBOverlap(this->Back->RigidBody->getAABB()))
		{
			robotPosition.z = 2.2f;
		}

		this->Robot->Transform->SetPosition(robotPosition);
		this->Scene->Physics->UpdateRigidBody(this->Robot->RigidBody, this->Robot->Transform);

		if (this->doorRotationDirection)
		{
			this->doorRotationAmount += this->doorRotationDirection * this->doorRotationSpeed * deltaTime;
			this->Front->Transform->Rotate(this->doorRotationDirection * this->doorRotationSpeed * deltaTime, 0.0f, 0.0f);
			this->Scene->Physics->UpdateRigidBody(this->FrontMeshObject->RigidBody, this->FrontMeshObject->Transform);

			if (this->doorRotationAmount >= glm::radians(90.0f) &&
				this->doorRotationDirection > 0)
			{
				this->doorRotationDirection = 0;
			}

			if (this->doorRotationAmount <= 0.0f &&
				this->doorRotationDirection < 0)
			{
				this->doorRotationDirection = 0;
			}
		}
	}

	GLSharedPtr<GPhysicsRectangle> Left;
	GLSharedPtr<GPhysicsRectangle> Right;
	GLSharedPtr<GPhysicsRectangle> Bottom;
	GLSharedPtr<GPhysicsRectangle> Top;
	GLSharedPtr<GPhysicsRectangle> Back;
	GLSharedPtr<GLGameObject> Front;
	GLSharedPtr<GPhysicsRectangle> FrontMeshObject;

	GLSharedPtr<GRobot> Robot;

	std::vector<GLSharedPtr<GPhysicsCube>> Obstacles;

	int doorRotationDirection = 0;
	float doorRotationAmount = 0.0f;
	float doorRotationSpeed = 1.0f;
};

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize()
	{
		this->Stage = GCreate(GStage);

		this->MainCamera = GCreate(GCameraController, 90.0f, -8.0f, 8.0f, -8.0f, 8.0f);

		this->AddChildren({ this->Stage, this->MainCamera });

		this->Stage->Initialize();
		this->MainCamera->Initialize();

		this->MainCamera->Transform->Translate(0.0f, 1.0f, 10.0f);
		this->MainCamera->Transform->Rotate(0.0f, 0.0f, 0.0f);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GWorld::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "i" || key == "I")
		{
			this->MainCamera->Transform->SetPosition(0.0f, 1.0f, 10.0f);
			this->MainCamera->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		}
		else if (key == "z")
		{
			this->CameraCurrentSpeed.z = 2.0f;
		}
		else if (key == "Z")
		{
			this->CameraCurrentSpeed.z = -2.0f;
		}
		else if (key == "x")
		{
			this->CameraCurrentSpeed.x = 2.0f;
		}
		else if (key == "X")
		{
			this->CameraCurrentSpeed.x = -2.0f;
		}
		else if (key == "y")
		{
			this->CameraCurrentRotationSpeed.y = 2.0f;
		}
		else if (key == "Y")
		{
			this->CameraCurrentRotationSpeed.y = -2.0f;
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
			OffSpeed(this->CameraCurrentSpeed.z, 2.0f);
		}
		else if (key == "Z")
		{
			OffSpeed(this->CameraCurrentSpeed.z, -2.0f);
		}
		else if (key == "x")
		{
			OffSpeed(this->CameraCurrentSpeed.x, 2.0f);
		}
		else if (key == "x")
		{
			OffSpeed(this->CameraCurrentSpeed.x, -2.0f);
		}
		else if (key == "y")
		{
			OffSpeed(this->CameraCurrentRotationSpeed.y, 2.0f);
		}
		else if (key == "Y")
		{
			OffSpeed(this->CameraCurrentRotationSpeed.y, -2.0f);
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->MainCamera->Transform->Translate(this->CameraCurrentSpeed * deltaTime);
		this->MainCamera->Transform->RotateAround(glm::vec3(0.0f, 0.0f, 0.0f),
			this->CameraCurrentRotationSpeed.y * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	GLSharedPtr<GStage> Stage;
	GLSharedPtr<GCameraController> MainCamera;

	glm::vec3 CameraCurrentSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 CameraCurrentRotationSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training22"));

	InitializeGLEW();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto scene = GLCreate<GLScene>("Training22");
	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
	GLLoadScene(scene);

	auto World = GCreate(GWorld);
	scene->Root->AddChild(World);
	World->Initialize();

	glutMainLoop();
}