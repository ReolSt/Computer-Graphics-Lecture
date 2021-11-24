#pragma once

#include <gl/glew.h>

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLTransform.h"
#include "GLMeshRenderer.h"

class GLPhysics
{
public:
	GLPhysics()
	{
		reactphysics3d::PhysicsWorld::WorldSettings settings;
		settings.isSleepingEnabled = false;
		settings.gravity = reactphysics3d::Vector3(0.0f, -9.81f, 0.0f);

		this->World = this->PhysicsCommon.createPhysicsWorld(settings);

		this->DebugMeshRenderer = GLCreate<GLMeshRenderer>();
		this->DebugMeshRenderer->GetMesh()->SetDrawMode(GLMeshDrawMode::Line);

		auto& debugRenderer = this->World->getDebugRenderer();
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
	}

	~GLPhysics()
	{
		this->PhysicsCommon.destroyPhysicsWorld(this->World);
	}

	void Update(float deltaTime)
	{
		this->World->update(deltaTime);
	}

	void Sync()
	{

	}

	void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition)
	{
		auto& renderer = this->World->getDebugRenderer();

		auto lines = renderer.getLines();

		auto mesh = this->DebugMeshRenderer->GetMesh();
		mesh->ClearVertices();
		mesh->ClearIndices();

		if (!this->World->getIsDebugRenderingEnabled())
		{
			return;
		}

		unsigned int index = 0;
		for (const auto& line : lines)
		{
			GLclampf color1 = line.color1 / 255.0f;
			GLclampf color2 = line.color2 / 255.0f;

			glm::vec3 p1(line.point1.x, line.point1.y, line.point1.z);
			glm::vec3 p2(line.point2.x, line.point2.y, line.point2.z);

			GLColor c1(color1, color1, color1, 1.0f);
			GLColor c2(color2, color2, color2, 1.0f);

			mesh->AddVertices({ p1, p2 });
			mesh->AddColors({ c1, c2 });
			mesh->AddIndices({ index, index + 1 });

			index += 2;
		}

		if (index > 0)
		{
			this->DebugMeshRenderer->Render(glm::mat4(1.0f), viewMatrix, projectionMatrix, cameraPosition);
		}
	}

	void SetDebug(bool debug)
	{
		this->World->setIsDebugRenderingEnabled(debug);;
	}

	bool GetDebug()
	{
		return this->World->getIsDebugRenderingEnabled();
	}

	reactphysics3d::Transform GetPhysicsTransform(const GLSharedPtr<GLTransform>& transform)
	{
		auto position = transform->GetPosition();
		auto rotation = transform->GetRotation();

		auto physicsPosition = reactphysics3d::Vector3(position.x, position.y, position.z);
		auto physicsRotation = reactphysics3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);
		physicsRotation.normalize();

		return reactphysics3d::Transform(physicsPosition, physicsRotation);
	}

	reactphysics3d::CollisionBody* CreateCollisionBody(const GLSharedPtr<GLTransform>& transform)
	{
		reactphysics3d::Transform physicsTransform = this->GetPhysicsTransform(transform);

		return this->World->createCollisionBody(physicsTransform);
	}

	reactphysics3d::CollisionBody* CreateCollisionBody(const reactphysics3d::Transform& transform)
	{
		return this->World->createCollisionBody(transform);
	}

	reactphysics3d::RigidBody* CreateRigidBody(const GLSharedPtr<GLTransform>& transform)
	{
		reactphysics3d::Transform physicsTransform = this->GetPhysicsTransform(transform);

		return this->World->createRigidBody(physicsTransform);
	}

	reactphysics3d::RigidBody* CreateRigidBody(const reactphysics3d::Transform& transform)
	{
		return this->World->createRigidBody(transform);
	}

	reactphysics3d::Joint* CreateJoint(const reactphysics3d::JointInfo& jointInfo)
	{
		return this->World->createJoint(jointInfo);
	}

	reactphysics3d::BoxShape* CreateBoxShape(const glm::vec3& halfExtends)
	{
		return this->PhysicsCommon.createBoxShape(reactphysics3d::Vector3(halfExtends.x, halfExtends.y, halfExtends.z));
	}

	reactphysics3d::BoxShape* CreateBoxShape(const reactphysics3d::Vector3& halfExtends)
	{
		return this->PhysicsCommon.createBoxShape(halfExtends);
	}

	reactphysics3d::SphereShape* CreateSphereShape(float radius)
	{
		return this->PhysicsCommon.createSphereShape(radius);
	}

	reactphysics3d::CapsuleShape* CreateCapsuleShape(float radius, float height)
	{
		return this->PhysicsCommon.createCapsuleShape(radius, height);
	}

	void DestroyCollisionBody(reactphysics3d::CollisionBody* collisionBody)
	{
		this->World->destroyCollisionBody(collisionBody);
	}

	void DestroyRigidBody(reactphysics3d::RigidBody* rigidBody)
	{
		this->World->destroyRigidBody(rigidBody);
	}

	void DestroyBoxShape(reactphysics3d::BoxShape* boxShape)
	{
		this->PhysicsCommon.destroyBoxShape(boxShape);
	}

	void DestroySphereShape(reactphysics3d::SphereShape* sphereShape)
	{
		this->PhysicsCommon.destroySphereShape(sphereShape);
	}

	void DestroyCapsuleShape(reactphysics3d::CapsuleShape* capsuleShape)
	{
		this->PhysicsCommon.destroyCapsuleShape(capsuleShape);
	}

	void UpdateCollisionBody(
		reactphysics3d::CollisionBody* collisionBody,
		const GLSharedPtr<GLTransform>& transform)
	{
		collisionBody->setTransform(this->GetPhysicsTransform(transform));
	}

	void UpdateRigidBody(
		reactphysics3d::RigidBody* rigidBody,
		const GLSharedPtr<GLTransform>& transform)
	{
		rigidBody->setTransform(this->GetPhysicsTransform(transform));
	}

	void UpdateRigidBodyPosition(
		reactphysics3d::RigidBody* rigidBody,
		const GLSharedPtr<GLTransform>& transform)
	{
		auto position = transform->GetPosition();

		auto physicsTransform = rigidBody->getTransform();
		physicsTransform.setPosition(reactphysics3d::Vector3(position.x, position.y, position.z));
	}

	void UpdateRigidBodyRotation(
		reactphysics3d::RigidBody* rigidBody,
		const GLSharedPtr<GLTransform>& transform)
	{
		auto rotation = transform->GetRotation();

		auto physicsTransform = rigidBody->getTransform();
		physicsTransform.setOrientation(reactphysics3d::Quaternion(rotation.w, rotation.x, rotation.y, rotation.z));

		rigidBody->setTransform(this->GetPhysicsTransform(transform));
	}

	void UpdateTransformFromPhysics(
		const GLSharedPtr<GLTransform>& transform,
		const reactphysics3d::Transform& physicsTransform)
	{
		const auto& physicsPosition = physicsTransform.getPosition();
		const auto& physicsRotation = physicsTransform.getOrientation();

		transform->SetPosition(physicsPosition.x, physicsPosition.y, physicsPosition.z);
		transform->SetRotation(physicsRotation.w, physicsRotation.x, physicsRotation.y, physicsRotation.z);
	}

	void UpdateTransformFromCollisionBody(
		const GLSharedPtr<GLTransform>& transform,
		const reactphysics3d::CollisionBody* collisionBody)
	{
		this->UpdateTransformFromPhysics(transform, collisionBody->getTransform());
	}

	void UpdateTransformFromRigidBody(
		const GLSharedPtr<GLTransform>& transform,
		const reactphysics3d::RigidBody* rigidBody)
	{
		this->UpdateTransformFromPhysics(transform, rigidBody->getTransform());
	}

protected:
	reactphysics3d::PhysicsCommon PhysicsCommon;
	reactphysics3d::PhysicsWorld* World;

	GLSharedPtr<GLMeshRenderer> DebugMeshRenderer;
};