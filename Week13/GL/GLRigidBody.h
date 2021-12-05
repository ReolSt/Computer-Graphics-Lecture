#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
#include "GLTransform.h"

using GLReactRigidBody = reactphysics3d::RigidBody;
using GLReactTransform = reactphysics3d::Transform;

using GLCollisionShape = reactphysics3d::CollisionShape;
using GLBoxShape = reactphysics3d::BoxShape;
using GLSphereShape = reactphysics3d::SphereShape;
using GLCapsuleShape = reactphysics3d::CapsuleShape;

using GLCollider = reactphysics3d::Collider;

using GLBodyType = reactphysics3d::BodyType;

class GLRigidBody
{
	static const reactphysics3d::BodyType DYNAMIC = reactphysics3d::BodyType::DYNAMIC;
	static const reactphysics3d::BodyType KIMEMATIC = reactphysics3d::BodyType::KINEMATIC;
	static const reactphysics3d::BodyType STATIC = reactphysics3d::BodyType::STATIC;
public:
	GLRigidBody(const GLSharedPtr<GLTransform>& transform)
	{
		this->Transform = transform;
	}

	~GLRigidBody()
	{

	}

	const GLReactRigidBody* getBody()
	{
		return this->Body;
	}

	void setBody(GLReactRigidBody* body)
	{
		this->Body = body;
	}

	GLBodyType getBodyType()
	{
		return this->Body->getType();
	}

	void setBodyType(const GLBodyType& bodyType)
	{
		this->Body->setType(bodyType);
	}

	const GLCollider* getCollider()
	{
		return this->Collider;
	}

	void setCollider(GLCollisionShape* shape, const GLReactTransform& transform)
	{
		if (this->Collider != nullptr)
		{
			this->Body->removeCollider(this->Collider);
		}

		this->Collider = this->Body->addCollider(shape, transform);
	}

	void removeCollider()
	{
		this->Body->removeCollider(this->Collider);
		this->Collider = nullptr;
	}

	const GLCollisionShape* getShape()
	{
		return this->Shape;
	}

	void Sync()
	{

	}

	void Update()
	{

	}

	GLSharedPtr<GLTransform> Transform;

	GLReactRigidBody* Body = nullptr;
	GLCollider* Collider = nullptr;
	GLCollisionShape* Shape = nullptr;
};