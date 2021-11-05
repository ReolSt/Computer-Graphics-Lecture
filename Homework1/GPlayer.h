#pragma once

#include "GL/GL.h"

#include "GPhysicsObject.h"
#include "GCameraController.h"

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

class GPlayer : public GPhysicsObject
{
public:
	GConstructor(GPlayer)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		this->MeshObject = GCreate(GCube);
		this->FirstPersonCamera = GCreate(GCameraController, 90.0f, -0.5f, 0.5f, -0.5f, 0.5f);
		this->QuaterViewCamera = GCreate(GCameraController);

		this->AddChildren({ this->MeshObject, this->FirstPersonCamera, this->QuaterViewCamera });

		this->MeshObject->Initialize();
		this->FirstPersonCamera->Initialize();
		this->QuaterViewCamera->Initialize();

		RandVertexColor3f(this->MeshObject);

		this->FirstPersonCamera->Transform->SetLocalPosition(0.0f, 0.2f, -0.2f);

		this->QuaterViewCamera->Transform->SetLocalPosition(0.0f, 5.0f, 5.0f);
		this->QuaterViewCamera->Transform->SetLocalEulerAngles(glm::radians(-45.0f), 0.0f, 0.0f);

		this->MeshObject->Transform->SetScale(0.6f, 0.6f, 0.6f);
		this->Transform->Translate(0.0f, 0.3f, 0.0f);

		this->ViewMode = 1;
		this->ActivateCamera();

		this->CollisionShape = this->Scene->Physics->CreateBoxShape(this->MeshObject->Transform->GetScale() / 2.0f);
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());

		this->RigidBody->setMass(10.0f);
		this->RigidBody->setIsActive(false);

		auto& material = this->Collider->getMaterial();
		material.setBounciness(0.0f);
		material.setRollingResistance(1.0f);

		this->UpdatePhysics();
	}

	void UpdatePhysics() override
	{
		GPhysicsObject::UpdatePhysics();

		auto halfExtents = this->MeshObject->Transform->GetScale();
	}

	void Activate()
	{
		this->Activated = true;
		this->ActivateCamera();
	}

	void Deactivate()
	{
		this->Activated = false;
		this->DeactivateCamera();
	}

	void ActivateCamera()
	{
		if (this->Activated)
		{
			if (this->ViewMode == 0)
			{
				this->FirstPersonCamera->Activate();
				this->QuaterViewCamera->Deactivate();
			}
			else if (this->ViewMode == 1)
			{
				this->FirstPersonCamera->Deactivate();
				this->QuaterViewCamera->Activate();
			}
		}
	}

	void DeactivateCamera()
	{
		this->FirstPersonCamera->Deactivate();
		this->QuaterViewCamera->Deactivate();
	}

	void SetViewMode(int mode)
	{
		this->ViewMode = mode;

		if (this->Activated)
		{
			this->ActivateCamera();
		}
	}

	void ToggleViewMode()
	{
		if (this->ViewMode == 0)
		{
			this->ViewMode = 1;
		}
		else if (this->ViewMode == 1)
		{
			this->ViewMode = 0;
		}

		if (this->Activated)
		{
			this->ActivateCamera();
		}
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto rotation = this->Transform->GetRotation();

		auto front = glm::rotate(rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		auto right = glm::rotate(rotation, glm::vec3(1.0f, 0.0f, 0.0f));
		auto up = glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f));

		auto velocity = this->CurrentSpeed.z * deltaTime * front + this->CurrentSpeed.x * deltaTime * right;
		this->RigidBody->setLinearVelocity(reactphysics3d::Vector3(velocity.x, velocity.y, velocity.z));

		this->Angle.x += this->RotationSpeed.x * deltaTime;
		this->Angle.y += this->RotationSpeed.y * deltaTime;

		this->FirstPersonCamera->Transform->SetLocalEulerAngles(this->Angle.x, 0.0f, 0.0f);
		this->Transform->SetLocalEulerAngles(0.0f, this->Angle.y, 0.0f);

		this->UpdatePhysics();
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GPlayer::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (!this->Activated)
		{
			return;
		}

		if (key == "w")
		{
			this->CurrentSpeed.z = -50.0f;
		}
		else if (key == "a")
		{
			this->CurrentSpeed.x = -50.0f;
		}
		else if (key == "s")
		{
			this->CurrentSpeed.z = 50.0f;
		}
		else if (key == "d")
		{
			this->CurrentSpeed.x = 50.0f;
		}
		else if (key == "x")
		{
			this->RotationSpeed.x = 2.0f;
		}
		else if (key == "X")
		{
			this->RotationSpeed.x = -2.0f;
		}
		else if (key == "y")
		{
			this->RotationSpeed.y = 2.0f;
		}
		else if (key == "Y")
		{
			this->RotationSpeed.y = -2.0f;
		}
		else if (key == "1")
		{
			this->SetViewMode(0);
		}
		else if (key == "3")
		{
			this->SetViewMode(1);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		std::cout << "[GPlayer::OnKeyUp] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "w")
		{
			OffSpeed(this->CurrentSpeed.z, -50.0f);
		}
		else if (key == "a")
		{
			OffSpeed(this->CurrentSpeed.x, -50.0f);
		}
		else if (key == "s")
		{
			OffSpeed(this->CurrentSpeed.z, 50.0f);
		}
		else if (key == "d")
		{
			OffSpeed(this->CurrentSpeed.x, 50.0f);
		}
		else if (key == "x")
		{
			this->RotationSpeed.x = 0.0f;
		}
		else if (key == "X")
		{
			this->RotationSpeed.x = 0.0f;
		}
		else if (key == "y")
		{
			this->RotationSpeed.y = 0.0f;
		}
		else if (key == "Y")
		{
			this->RotationSpeed.y = 0.0f;
		}
	}

	GLSharedPtr<GCube> MeshObject;
	GLSharedPtr<GCameraController> FirstPersonCamera;
	GLSharedPtr<GCameraController> QuaterViewCamera;

	int ViewMode = 0;
	bool Activated = false;

	glm::vec3 Speed = glm::vec3(2.0f);
	glm::vec3 CurrentSpeed = glm::vec3(0.0f);
	glm::vec3 RotationSpeed = glm::vec3(0.0f);
	glm::vec3 Angle = glm::vec3(0.0f, 0.0f, 0.0f);

	reactphysics3d::Collider* Collider;
	reactphysics3d::BoxShape* CollisionShape;
};