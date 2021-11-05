#pragma once

#include "GL/GL.h"

#include "GPhysicsObject.h"

class GMazeWall : public GPhysicsObject
{
public:
	GConstructor(GMazeWall)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		this->MeshObject = GCreate(GCube);
		this->AddChild(this->MeshObject);

		this->RigidBody->setType(reactphysics3d::BodyType::STATIC);
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(this->MeshObject->Transform->GetScale() / 2.0f);
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());

		auto& material = this->Collider->getMaterial();
		material.setBounciness(0.0f);

		this->MinHeight = Rand(1.0f, 3.0f);
		this->MaxHeight = Rand(6.0f, 12.0f);
		this->HeightTransitionSpeed = Rand(2.0f, 4.0f);

		this->RandHeight();
	}

	void RefreshCollider()
	{
		this->RigidBody->removeCollider(this->Collider);

		this->CollisionShape = this->Scene->Physics->CreateBoxShape(this->Transform->GetScale() / 2.0f);
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());
	}

	void UpdateMesh()
	{
		this->MeshObject->Transform->LocalScale.y = this->CurrentHeight;
		this->MeshObject->Transform->LocalPosition.y = this->CurrentHeight / 2;

		auto halfExtent = this->MeshObject->Transform->GetScale() / 2.0f;
		auto halfExtentPhysics = reactphysics3d::Vector3(halfExtent.x, halfExtent.y, halfExtent.z);

		this->CollisionShape->setHalfExtents(halfExtentPhysics);
		this->Scene->Physics->UpdateRigidBody(this->RigidBody, this->MeshObject->Transform);
	}

	void RandHeight()
	{
		this->SetHeight(Rand(this->MinHeight, this->MaxHeight));
	}

	void SetHeight(float height)
	{
		this->CurrentHeight = height;

		this->UpdateMesh();
	}

	void OnKeyDown(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "v")
		{
			if (!this->HeightFixed)
			{
				this->HeightTransition = false;
				this->HeightFixed = true;
				this->OriginalHeight = this->CurrentHeight;
				this->SetHeight(2.0f);
			}
			else
			{
				this->HeightTransition = true;
				this->HeightFixed = false;
				this->SetHeight(this->OriginalHeight);
			}
		}
		else if (key == "m")
		{
			if (!this->HeightFixed)
			{
				this->HeightTransition = true;
			}
		}
		else if (key == "M")
		{
			this->HeightTransition = false;
		}
		else if (key == "+" || key == "=")
		{
			this->HeightTransitionSpeed += 1.0f;
		}
		else if (key == "-")
		{
			this->HeightTransitionSpeed -= 1.0f;
			this->HeightTransitionSpeed = glm::max(0.0f, this->HeightTransitionSpeed);
		}
	}

	void Update(float deltaTime) override
	{
		this->Scene->Physics->UpdateTransformFromRigidBody(this->MeshObject->Transform, this->RigidBody);

		if (this->HeightTransition)
		{
			this->CurrentHeight += this->HeightTransitionDirection * deltaTime * this->HeightTransitionSpeed;

			if (this->CurrentHeight > this->MaxHeight)
			{
				this->CurrentHeight = this->MaxHeight;
				this->HeightTransitionDirection = -1;
			}
			else if (this->CurrentHeight < this->MinHeight)
			{
				this->CurrentHeight = this->MinHeight;
				this->HeightTransitionDirection = 1;
			}
		}

		this->UpdateMesh();
	}

	float MinHeight = 1.0f;
	float MaxHeight = 10.0f;
	float CurrentHeight = 1.0f;
	float OriginalHeight = 1.0f;

	bool HeightTransition = true;
	bool HeightFixed = false;
	int HeightTransitionDirection = 1;
	float HeightTransitionSpeed = 3.0f;

	GLSharedPtr<GCube> MeshObject;

	reactphysics3d::Collider* Collider;
	reactphysics3d::BoxShape* CollisionShape;
};