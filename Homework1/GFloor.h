#pragma once

#include "GL/GL.h"

#include "GPhysicsObject.h"

class GFloor : public GPhysicsObject
{
public:
	GConstructor(GFloor)
		: GSuperClassInitializer(GPhysicsObject) { }

	void Initialize() override
	{
		GPhysicsObject::Initialize();
		this->MeshRenderer->Mesh = GLCreate<GLRectangleMesh>();

		auto worldScale = this->Transform->GetScale();
		this->CollisionShape = this->Scene->Physics->CreateBoxShape(reactphysics3d::Vector3(worldScale.x, 0.2f, worldScale.z) / 2.0f);
		this->Collider = this->RigidBody->addCollider(this->CollisionShape, reactphysics3d::Transform());

		this->RigidBody->setType(reactphysics3d::BodyType::STATIC);

		auto& material = this->Collider->getMaterial();
		material.setBounciness(0.0f);

		this->UpdatePhysics();
	}

	void UpdatePhysics() override
	{
		GPhysicsObject::UpdatePhysics();

		auto halfExtends = this->Transform->GetScale() / 2.0f;
		auto physicsHalfExtends = reactphysics3d::Vector3(halfExtends.x, halfExtends.y, halfExtends.z);
		this->CollisionShape->setHalfExtents(physicsHalfExtends);
	}

	reactphysics3d::Collider* Collider;
	reactphysics3d::BoxShape* CollisionShape;
};