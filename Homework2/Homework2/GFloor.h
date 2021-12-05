#pragma once

#include "../GL/GL.h"

#include "GPhysicsPrimitives.h"

class GFloor : public GPhysicsObject
{
public:
	GConstructor(GFloor)
		: GSuperClassInitializer(GPhysicsObject)
	{

	}

	void Initialize() override
	{
		GPhysicsObject::Initialize();

		auto transform = this->GetTransform();

		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto mesh = GLMeshLoader::Load("resources/Cube.obj");
		auto texture = GLTextureLoader::Load("resources/Brick.png");

		meshRenderer->SetMesh(mesh);
		material->SetDiffuseMap(texture);

		this->GetTransform()->SetLocalScale(5.0f, 0.5f, 5.0f);

		this->RigidBody = GLGetCurrentScene()->GetPhysics()->CreateRigidBody(this->GetTransform());
		this->CollisionShape = GLGetCurrentScene()->GetPhysics()->CreateBoxShape(glm::vec3(5.0f, 0.5f, 5.0f));

		this->RigidBody->setType(GLBodyType::KINEMATIC);

		auto* collider = this->RigidBody->addCollider(this->CollisionShape, GLPhysicsTransform());
		this->UpdateBody();
	}

	void Update(float deltaTime) override
	{
		GPhysicsObject::Update(deltaTime);
	}

	void RemapTexture()
	{
		auto meshRenderer = this->GetMeshRenderer();
		auto mesh = meshRenderer->GetMesh();

		auto scale = this->GetTransform()->GetScale();

		for (int i = 0; i < mesh->GetUVCount(); ++i)
		{
			auto uv = mesh->GetUV(i);

			mesh->SetUV(i, uv * glm::vec2(scale.x, scale.z));
		}
	}

	reactphysics3d::CollisionShape* CollisionShape;
};
