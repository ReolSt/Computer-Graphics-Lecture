#pragma once

#include "GL/GL.h"

class GPhysicsObject : public GLGameObject
{
public:
	GConstructor(GPhysicsObject)
		: GSuperClassInitializer(GLGameObject) { }

	virtual ~GPhysicsObject()
	{
		this->Scene->Physics->DestroyRigidBody(this->RigidBody);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->RigidBody = this->Scene->Physics->CreateRigidBody(this->Transform);
	}

	void Update(float deltaTime) override
	{
		this->Scene->Physics->UpdateTransformFromRigidBody(this->Transform, this->RigidBody);
	}

	virtual void UpdatePhysics()
	{
		this->Scene->Physics->UpdateRigidBody(this->RigidBody, this->Transform);
	}

	reactphysics3d::RigidBody* RigidBody;
};