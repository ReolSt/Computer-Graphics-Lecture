#pragma once

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

class GEraser : public GLGameObject
{
public:
	GConstructor(GEraser)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->LowerBody = GCreate(GCube);
		this->UpperBody = GCreate(GCube);

		this->LowerBody->Transform->SetScale(1.0f, 0.5f, 1.0f);
		this->LowerBody->Transform->Translate(0.0f, 0.0f, 0.0f);

		this->UpperBody->Transform->SetScale(0.5f, 1.0f, 0.5f);
		this->UpperBody->Transform->Translate(0.0f, 0.75f, 0.0f);

		this->LowerBody->Initialize();
		this->UpperBody->Initialize();

		RandVertexColor3f(this->LowerBody);
		RandVertexColor3f(this->UpperBody);

		this->AddChildren({ this->LowerBody, this->UpperBody });

		this->Transform->Translate(0.0f, 2.0f, 0.0f);

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(glm::vec3(0.5f, 0.25f, 0.5f));

		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
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
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto physicsTransform = this->RigidBody->getTransform();

		auto physicsPosition = physicsTransform.getPosition();

		physicsPosition.x += this->CurrentSpeed.x * deltaTime;
		physicsPosition.y += this->CurrentSpeed.y * deltaTime;
		physicsPosition.z += this->CurrentSpeed.z * deltaTime;

		physicsTransform.setPosition(physicsPosition);
		physicsTransform.setOrientation(reactphysics3d::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

		this->RigidBody->setTransform(physicsTransform);
		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	GLSharedPtr<GCube> LowerBody;
	GLSharedPtr<GCube> UpperBody;

	reactphysics3d::RigidBody* RigidBody = nullptr;
	reactphysics3d::BoxShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;

	glm::vec3 CurrentSpeed = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Speed = glm::vec3(2.0f, 2.0f, 2.0f);
};

class GRemovableObject : public GCube
{
public:
	GConstructor(GRemovableObject)
		: GSuperClassInitializer(GCube) { }

	virtual ~GRemovableObject()
	{
		this->Scene->Physics->DestroyRigidBody(this->RigidBody);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		SetVertexColor(this->MeshRenderer->Mesh, RandColor3f());

		auto scale = this->Transform->GetScale();

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(scale * 0.5f);
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());

		this->RigidBody->setMass(100.0f);
		this->RigidBody->enableGravity(false);
		this->Collider->setIsTrigger(true);
		auto& material = this->Collider->getMaterial();
		material.setBounciness(0.0f);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		if (this->bIsRemovingItself)
		{
			this->Transform->SetScale(OriginalScale * this->RemainingTime / 2.0f);
			this->RemainingTime = glm::max(0.0f, this->RemainingTime - deltaTime);
		}

		auto physicsTransform = this->RigidBody->getTransform();
		auto physicsPosition = physicsTransform.getPosition();

		physicsTransform.setPosition(physicsPosition);
		physicsTransform.setOrientation(reactphysics3d::Quaternion(0.0f, 0.0f, 0.0f, 1.0f));

		this->RigidBody->setTransform(physicsTransform);

		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	void Remove()
	{
		this->bIsRemovingItself = true;
		this->OriginalScale = this->Transform->GetScale();
		this->RigidBody->removeCollider(this->Collider);
	}

	bool IsRemoving()
	{
		return this->bIsRemovingItself;
	}

	bool bIsRemovingItself = false;
	glm::vec3 OriginalScale;
	float RemainingTime = 2.0f;

	reactphysics3d::RigidBody* RigidBody = nullptr;
	reactphysics3d::BoxShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;
};

class GFloor : public GRectangle
{
public:
	GConstructor(GFloor)
		: GSuperClassInitializer(GRectangle) { }

	void Initialize()
	{
		GLGameObject::Initialize();

		this->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		this->Transform->Translate(0.0f, -2.0f, 0.0f);
		this->Transform->SetScale(10.0f, 10.0f, 1.0f);

		RandVertexColor3f(this->MeshRenderer->Mesh);

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(glm::vec3(5.0f, 5.0f, 0.1f));
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		this->RigidBody->setType(reactphysics3d::BodyType::KINEMATIC);

		auto& material = this->Collider->getMaterial();
		material.setBounciness(0.0f);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	reactphysics3d::RigidBody* RigidBody = nullptr;
	reactphysics3d::BoxShape* CollisionShape = nullptr;
	reactphysics3d::Collider* Collider = nullptr;
};

class GWhiteBoard3D : public GLGameObject
{
public:
	GConstructor(GWhiteBoard3D)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Eraser = GCreateChild(GEraser);
		this->Floor = GCreateChild(GFloor);

		this->Eraser->Initialize();
		this->Floor->Initialize();

		this->AddChildren({ this->Floor, this->Eraser });

		this->Reset();
	}

	void Reset()
	{
		for (const auto& object : this->RemovableObjects)
		{
			this->RemoveChild(object);
		}
		this->RemovableObjects.clear();

		auto objectCount = Rand(10, 30);
		for (auto i = 0; i < objectCount; ++i)
		{
			auto removableObject = GCreate(GRemovableObject);
			removableObject->Transform->SetScale(Rand(0.1f, 0.8f), 0.5f, Rand(0.1f, 0.8f));
			removableObject->Transform->Translate(Rand(-4.5f, 4.5f), -1.75f, Rand(-4.5f, 4.5f));

			this->AddChild(removableObject);
			this->RemovableObjects.push_back(removableObject);
			removableObject->Initialize();
		}
	}

	void OnKeyDown(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "c" || key == "C")
		{
			this->Reset();
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto eraserPosition = this->Eraser->Transform->GetPosition();
		auto eraserScale = this->Eraser->Transform->GetScale();

		for (auto itr = this->RemovableObjects.begin(); itr != this->RemovableObjects.end(); ++itr)
		{
			const auto& object = (*itr);

			if (object->IsRemoving())
			{
				if(object->RemainingTime <= 0.0f)
				{
					this->RemoveChild(object);
					this->RemovableObjects.erase(itr);
					break;
				}
			}

			if (this->Eraser->RigidBody->testAABBOverlap(object->RigidBody->getAABB()))
			{
				object->Remove();
			}
		}
	}

	std::vector<GLSharedPtr<GRemovableObject>> RemovableObjects;

	GLSharedPtr<GEraser> Eraser;
	GLSharedPtr<GLGameObject> Floor;
};

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize()
	{
		GLGameObject::Initialize();

		this->WhiteBoard = GCreate(GWhiteBoard3D);
		this->MainCamera = GCreate(GCameraController, 90.0f, -8.0f, 8.0f, -8.0f, 8.0f);

		this->AddChildren({ this->WhiteBoard, this->MainCamera });

		this->WhiteBoard->Initialize();
		this->MainCamera->Initialize();

		this->MainCamera->Transform->Translate(0.0f, 5.5f, 5.5f);
		this->MainCamera->Transform->Rotate(glm::radians(-45.0f), 0.0f, 0.0f);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GWorld::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "Tab")
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

	GLSharedPtr<GWhiteBoard3D> WhiteBoard;
	GLSharedPtr<GCameraController> MainCamera;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training21"));

	InitializeGLEW();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto scene = GLCreate<GLScene>("Training21");
	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));
	GLLoadScene(scene);

	auto World = GCreate(GWorld);
	scene->Root->AddChild(World);
	World->Initialize();

	glutMainLoop();
}