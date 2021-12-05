#pragma once

#include "../GL/GL.h"

#include "Helpers.h"
#include "GPhysicsPrimitives.h"

class GObstacle : public GPhysicsObject
{
public:
	GConstructor(GObstacle)
		: GSuperClassInitializer(GPhysicsObject) { }

	virtual ~GObstacle() { }

	void Initialize()
	{
		GPhysicsObject::Initialize();

		this->GetMeshRenderer()->SetMesh(GLMeshLoader::Load("resources/Cube.obj"));

		auto scene = GLGetCurrentScene();

		this->RigidBody = scene->GetPhysics()->CreateRigidBody(this->GetTransform());
		this->CollisionShape = scene->GetPhysics()->CreateBoxShape(glm::vec3(0.2f, 0.2f, 0.2f));

		this->RigidBody->setType(GLBodyType::KINEMATIC);

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, GLPhysicsTransform());
		auto& material = collider->getMaterial();

		material.setRollingResistance(1.0f);
		material.setBounciness(0.0f);

		this->GetTransform()->SetEulerAngles(glm::radians(45.0f), glm::radians(45.0f), glm::radians(45.0f));

		this->GetTransform()->SetLocalScale(0.2f, 0.2f, 0.2f);
		this->UpdateBody();
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);

		this->GetTransform()->Rotate(deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
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

	reactphysics3d::BoxShape* CollisionShape;
};
