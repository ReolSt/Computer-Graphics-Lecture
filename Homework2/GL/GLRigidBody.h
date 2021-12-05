#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
#include "GLTransform.h"

using GLReactRigidBody = reactphysics3d::RigidBody;
using GLReactTransform = reactphysics3d::Transform;

using GLCollisionShape = reactphysics3d::CollisionShape;
using GLBoxShape = reactphysics3d::BoxShape;
using GLCapsuleShape = reactphysics3d::CapsuleShape;

using GLCollider = reactphysics3d::Collider;
using GLPhysicsMaterial = reactphysics3d::Material;

using GLBodyType = reactphysics3d::BodyType;

enum class GLPhysicsShapeType
{
	GLEmptyShape = 0,
	GLBoxShape = 1,
	GLCapsuleShape = 2
};

class GLRigidBody
{
public:
	static const GLBodyType DYNAMIC = GLBodyType::DYNAMIC;
	static const GLBodyType KIMEMATIC = GLBodyType::KINEMATIC;
	static const GLBodyType STATIC = GLBodyType::STATIC;
public:
	GLRigidBody(GLGameObject* gameObject)
	{
		this->gameObject = gameObject;
	}

	virtual ~GLRigidBody()
	{

	}

	GLReactRigidBody* GetBody()
	{
		return this->body;
	}

	void SetBody(GLReactRigidBody* body)
	{
		this->body = body;
		this->body->enableGravity(true);
	}

	GLBodyType GetBodyType()
	{
		return this->body->getType();
	}

	void SetBodyType(GLBodyType bodyType)
	{
		this->body->setType(bodyType);
	}

	glm::vec3 GetLinearVelocity()
	{
		auto velocity = this->body->getLinearVelocity();

		return glm::vec3(velocity.x, velocity.y, velocity.z);
	}

	void SetLinearVelocity(float x, float y, float z)
	{
		this->body->setLinearVelocity(reactphysics3d::Vector3(x, y, z));
	}

	void SetLinearVelocity(const glm::vec3& velocity)
	{
		SetLinearVelocity(velocity.x, velocity.y, velocity.z);
	}

	const GLCollider* GetCollider()
	{
		return this->collider;
	}

	void SetCollider(GLCollisionShape* shape, const GLReactTransform& transform)
	{
		this->RemoveCollider();

		this->collider = this->body->addCollider(shape, transform);
	}

	void RemoveCollider()
	{
		if (this->collider != nullptr)
		{
			this->body->removeCollider(this->collider);
		}

		this->collider = nullptr;
	}

	GLPhysicsMaterial& GetMaterial()
	{
		return this->collider->getMaterial();
	}

	const GLCollisionShape* GetShape()
	{
		return this->shape;
	}

	void SetShape(GLCollisionShape* shape)
	{
		this->shape = shape;
	}

	GLPhysicsShapeType GetShapeType()
	{
		return this->shapeType;
	}

	void SetShapeType(GLPhysicsShapeType shapeType)
	{
		if (shapeType != this->shapeType)
		{
			this->RemoveShape();
			this->RemoveCollider();
		}

		if (shapeType == GLPhysicsShapeType::GLBoxShape)
		{
			auto extent = this->gameObject->GetTransform()->GetScale() / 2.0f;

			this->shape = this->physicsCommon.createBoxShape(reactphysics3d::Vector3(extent.x, extent.y, extent.z));
			this->collider = this->body->addCollider(this->shape, GLReactTransform());
		}
		else if (shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			auto scale = this->gameObject->GetTransform()->GetScale();

			this->shape = this->physicsCommon.createCapsuleShape((scale.x + scale.z) / 4.0f, scale.y / 2.0f);
			this->collider = this->body->addCollider(this->shape, GLReactTransform());
		}

		this->shapeType = shapeType;
	}

	void RemoveShape()
	{
		if (this->shapeType == GLPhysicsShapeType::GLBoxShape)
		{
			this->physicsCommon.destroyBoxShape(dynamic_cast<GLBoxShape*>(this->shape));
		}
		else if (this->shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			this->physicsCommon.destroyCapsuleShape(dynamic_cast<GLCapsuleShape*>(this->shape));
		}

		this->shape = nullptr;
	}

	glm::vec3 GetHalfExtents()
	{
		if (this->shapeType == GLPhysicsShapeType::GLBoxShape)
		{
			auto halfExtents = dynamic_cast<GLBoxShape*>(this->shape)->getHalfExtents();

			return glm::vec3(halfExtents.x, halfExtents.y, halfExtents.z);
		}
		
		return glm::vec3(0.0f);
	}

	float GetRadius()
	{
		if (this->shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			return dynamic_cast<GLCapsuleShape*>(this->shape)->getRadius();
		}

		return 0.0f;
	}

	float GetHeight()
	{
		if (this->shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			return dynamic_cast<GLCapsuleShape*>(this->shape)->getHeight();
		}

		return 0.0f;
	}


	void SetHalfExtents(const glm::vec3& halfExtents)
	{
		if (this->shapeType == GLPhysicsShapeType::GLBoxShape)
		{
			auto physicsHalfExtents = reactphysics3d::Vector3(halfExtents.x, halfExtents.y, halfExtents.z);
			dynamic_cast<GLBoxShape*>(this->shape)->setHalfExtents(reactphysics3d::Vector3(physicsHalfExtents));
		}
	}

	void SetRadius(float radius)
	{
		if (this->shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			dynamic_cast<GLCapsuleShape*>(this->shape)->setRadius(radius);
		}
	}

	void SetHeight(float height)
	{
		if (this->shapeType == GLPhysicsShapeType::GLCapsuleShape)
		{
			dynamic_cast<GLCapsuleShape*>(this->shape)->setHeight(height);
		}
	}

	reactphysics3d::Transform GetPhysicsTransform()
	{
		auto transform = this->gameObject->GetTransform();

		auto position = transform->GetPosition();
		auto rotation = transform->GetRotation();

		auto physicsPosition = reactphysics3d::Vector3(position.x, position.y, position.z);
		auto physicsRotation = reactphysics3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
		physicsRotation.normalize();

		return reactphysics3d::Transform(physicsPosition, physicsRotation);
	}

	void Sync()
	{
		body->setTransform(this->GetPhysicsTransform());
	}

	void Update()
	{
		auto transform = this->gameObject->GetTransform();

		auto physicsTransform = this->GetPhysicsTransform();
		const auto& physicsPosition = physicsTransform.getPosition();
		const auto& physicsRotation = physicsTransform.getOrientation();

		transform->SetPosition(physicsPosition.x, physicsPosition.y, physicsPosition.z);
		transform->SetRotation(physicsRotation.w, physicsRotation.x, physicsRotation.y, physicsRotation.z);
	}

private:
	GLGameObject* gameObject;

	GLReactRigidBody* body = nullptr;
	GLCollider* collider = nullptr;
	GLCollisionShape* shape = nullptr;
	GLPhysicsShapeType shapeType = GLPhysicsShapeType::GLEmptyShape;

	reactphysics3d::PhysicsCommon physicsCommon;
};