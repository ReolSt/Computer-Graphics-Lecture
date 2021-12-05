#pragma once

#include "../GL/GL.h"

class GPhysicsObject : public GLGameObject
{
public:
	GConstructor(GPhysicsObject)
		: GSuperClassInitializer(GLGameObject) { }

	virtual ~GPhysicsObject()
	{
		auto scene = GLGetCurrentScene();

		if (this->RigidBody != nullptr)
		{
			scene->GetPhysics()->DestroyRigidBody(this->RigidBody);
		}
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->UpdateTransform();
	}

	void UpdateTransform()
	{
		auto scene = GLGetCurrentScene();

		if (scene)
		{
			scene->GetPhysics()->UpdateTransformFromRigidBody(this->GetTransform(), this->RigidBody);
		}
	}

	void UpdateBody()
	{
		auto scene = GLGetCurrentScene();

		if (scene)
		{
			scene->GetPhysics()->UpdateRigidBody(this->RigidBody, this->GetTransform());
		}
	}

	reactphysics3d::RigidBody* RigidBody = nullptr;
};