#pragma once

#include "../GL/GL.h"

#include "Helpers.h"
#include "GPhysicsPrimitives.h"

class GRobot : public GPhysicsObject
{
public:
	GConstructor(GRobot)
		: GSuperClassInitializer(GPhysicsObject) { }

	virtual ~GRobot() { }

	void Initialize()
	{
		GPhysicsObject::Initialize();

		this->head = GCreate(GCube);
		this->nose = GCreate(GCube);
		this->body = GCreate(GCube);
		this->leftArmAxis = GCreate(GLGameObject);
		this->leftArm = GCreate(GCube);
		this->rightArmAxis = GCreate(GLGameObject);
		this->rightArm = GCreate(GCube);
		this->leftLegAxis = GCreate(GLGameObject);
		this->leftLeg = GCreate(GCube);
		this->rightLegAxis = GCreate(GLGameObject);
		this->rightLeg = GCreate(GCube);

		this->head->GetTransform()->Translate(0.0f, 0.45f, 0.0f);
		this->head->GetTransform()->SetScale(0.2f, 0.25f, 0.2f);

		this->nose->GetTransform()->Translate(0.0f, 0.45f, 0.1125f);
		this->nose->GetTransform()->SetScale(0.025f, 0.05f, 0.025f);

		this->body->GetTransform()->Translate(0.0f, 0.1f, 0.0f);
		this->body->GetTransform()->SetScale(0.35f, 0.5f, 0.3f);

		this->leftArmAxis->GetTransform()->Translate(-0.2f, 0.35f, 0.0f);

		this->leftArm->GetTransform()->Translate(0.0f, -0.25f, 0.0f);
		this->leftArm->GetTransform()->SetScale(0.1f, 0.5f, 0.1f);

		this->rightArmAxis->GetTransform()->Translate(0.2f, 0.35f, 0.0f);

		this->rightArm->GetTransform()->Translate(0.0f, -0.25f, 0.0f);
		this->rightArm->GetTransform()->SetScale(0.1f, 0.5f, 0.1f);

		this->leftLegAxis->GetTransform()->Translate(-0.1f, -0.2f, 0.0f);

		this->leftLeg->GetTransform()->Translate(0.0f, -0.15f, 0.0f);
		this->leftLeg->GetTransform()->SetScale(0.1f, 0.5f, 0.1f);

		this->rightLegAxis->GetTransform()->Translate(0.1f, -0.2f, 0.0f);

		this->rightLeg->GetTransform()->Translate(0.0f, -0.15f, 0.0f);
		this->rightLeg->GetTransform()->SetScale(0.1f, 0.5f, 0.1f);

		this->AddChildren({
			this->head, this->nose, this->body, this->leftArmAxis, this->rightArmAxis, this->leftLegAxis, this->rightLegAxis });

		this->leftArmAxis->AddChild(this->leftArm);
		this->rightArmAxis->AddChild(this->rightArm);

		this->leftLegAxis->AddChild(this->leftLeg);
		this->rightLegAxis->AddChild(this->rightLeg);

		this->RigidBody = GLGetCurrentScene()->GetPhysics()->CreateRigidBody(this->GetTransform());
		this->CollisionShape = GLGetCurrentScene()->GetPhysics()->CreateCapsuleShape(0.22f, 0.7f);

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
		auto& material = collider->getMaterial();

		material.setRollingResistance(1.0f);
		material.setBounciness(0.0f);

		collider->setMaterial(material);
		this->UpdateBody();

		auto texture = GLTextureLoader::Load("resources/Wood.jpg");

		this->head->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->nose->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->body->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->leftArm->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->rightArm->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->leftLeg->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
		this->rightLeg->GetMeshRenderer()->GetMaterial()->SetDiffuseMap(texture);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "i")
		{
			this->currentSpeed.z = -this->speed.z;
		}
		else if (key == "j")
		{
			this->currentSpeed.x = -this->speed.x;
		}
		else if (key == "k")
		{
			this->currentSpeed.z = this->speed.z;
		}
		else if (key == "l")
		{
			this->currentSpeed.x = this->speed.x;
		}
		else if (key == "Space")
		{
			if (!this->bIsJumping)
			{
				this->RigidBody->setLinearVelocity(reactphysics3d::Vector3(0.0f, 5.0f, 0.0f));
				this->bIsJumping = true;
			}
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "i")
		{
			OffSpeed(this->currentSpeed.z, -this->speed.z);
		}
		else if (key == "j")
		{
			OffSpeed(this->currentSpeed.x, -this->speed.x);
		}
		else if (key == "k")
		{
			OffSpeed(this->currentSpeed.z, this->speed.z);
		}
		else if (key == "l")
		{
			OffSpeed(this->currentSpeed.x, this->speed.x);
		}
		else if (key == "Space")
		{
			this->bIsJumping = false;
		}
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		auto speed = this->currentSpeed * deltaTime;
		this->GetTransform()->Translate(speed.x, speed.y, speed.z);

		if (speed.x != 0.0f || speed.y != 0.0f || speed.z != 0.0f)
		{
			if (!this->swingDirection)
			{
				this->swingDirection = 1;
			}
		}
		else if (speed.x == 0.0f && speed.y == 0.0f && speed.z == 0.0f)
		{
			this->swingDirection = 0;
			this->leftArmAxis->GetTransform()->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->rightArmAxis->GetTransform()->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->leftLegAxis->GetTransform()->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->rightLegAxis->GetTransform()->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			this->swingAmount = 0.0f;
		}

		if (this->swingDirection)
		{
			this->leftArmAxis->GetTransform()->SetLocalEulerAngles(this->swingAmount, 0.0f, 0.0f);
			this->rightArmAxis->GetTransform()->SetLocalEulerAngles(-this->swingAmount, 0.0f, 0.0f);
			this->leftLegAxis->GetTransform()->SetLocalEulerAngles(-this->swingAmount, 0.0f, 0.0f);
			this->rightLegAxis->GetTransform()->SetLocalEulerAngles(this->swingAmount, 0.0f, 0.0f);
			this->swingAmount += this->swingDirection * this->swingSpeed * deltaTime;

			if (this->swingDirection > 0 && this->swingAmount >= glm::radians(45.0f))
			{
				this->swingDirection = -1;
			}
			else if (this->swingDirection < 0 && this->swingAmount <= glm::radians(-45.0f))
			{
				this->swingDirection = 1;
			}
		}

		if (this->currentSpeed.x > 0.0f)
		{
			this->angle = glm::radians(90.0f);
		}
		else if (this->currentSpeed.x < 0.0f)
		{
			this->angle = glm::radians(270.0f);
		}

		if (this->currentSpeed.z > 0)
		{
			if (this->angle != 0.0f)
			{
				this->angle = (this->angle + glm::radians(glm::degrees(this->angle) > 180.0f ? 360.0f : 0.0f)) / 2.0f;
			}
			else
			{
				this->angle = 0.0f;
			}
		}
		else if (this->currentSpeed.z < 0)
		{
			if (this->angle != 0.0f)
			{
				this->angle = (this->angle + glm::radians(180.0f)) / 2.0f;
			}
			else
			{
				this->angle = glm::radians(180.0f);
			}
		}

		this->GetTransform()->SetEulerAngles(0.0f, angle, 0.0f);
		this->UpdateBody();
	}

	GLSharedPtr<GLGameObject> head;
	GLSharedPtr<GLGameObject> nose;
	GLSharedPtr<GLGameObject> body;
	GLSharedPtr<GLGameObject> leftArmAxis;
	GLSharedPtr<GLGameObject> leftArm;
	GLSharedPtr<GLGameObject> rightArmAxis;
	GLSharedPtr<GLGameObject> rightArm;
	GLSharedPtr<GLGameObject> leftLegAxis;
	GLSharedPtr<GLGameObject> leftLeg;
	GLSharedPtr<GLGameObject> rightLegAxis;
	GLSharedPtr<GLGameObject> rightLeg;

	glm::vec3 currentSpeed = glm::vec3(0.0f);
	glm::vec3 speed = glm::vec3(1.0f);

	float angle = 0.0f;

	int swingDirection = 0;
	float swingAmount = 0.0f;
	float swingSpeed = 3.0f;

	bool bIsJumping = false;

	reactphysics3d::CapsuleShape* CollisionShape;
};
