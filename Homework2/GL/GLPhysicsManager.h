#pragma once

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLTransform.h"
#include "GLMeshRenderer.h"
#include "GLRigidBody.h"

class GLPhysicsManager
{
public:
	GLPhysicsManager()
	{
		reactphysics3d::PhysicsWorld::WorldSettings settings;
		settings.isSleepingEnabled = false;
		settings.gravity = reactphysics3d::Vector3(0.0f, -9.81f, 0.0f);

		this->World = this->PhysicsCommon.createPhysicsWorld(settings);

		this->DebugMeshRenderer = GLCreate<GLMeshRenderer>();
		this->DebugMeshRenderer->GetMesh()->SetDrawMode(GLMeshDrawMode::Line);
		this->DebugMeshRenderer->GetMaterial()->SetShader(GLCreate<GLBasicShader>());

		auto& debugRenderer = this->World->getDebugRenderer();
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_NORMAL, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
		debugRenderer.setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
	}

	~GLPhysicsManager()
	{
		this->PhysicsCommon.destroyPhysicsWorld(this->World);
	}

	void Update(float deltaTime)
	{
		this->World->update(deltaTime);

		for (auto& rigidBody : this->rigidBodies)
		{
			rigidBody->Update();
		}
	}

	void Sync()
	{
		for (auto& rigidBody : this->rigidBodies)
		{
			rigidBody->Sync();
		}
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

		std::cout << lines.size() << std::endl;
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

	reactphysics3d::RigidBody* CreateBody(GLRigidBody* body)
	{
		auto reactBody = this->World->createRigidBody(body->GetPhysicsTransform());

		this->rigidBodies.push_back(body);
		return reactBody;
	}

	reactphysics3d::Joint* CreateJoint(const reactphysics3d::JointInfo& jointInfo)
	{
		return this->World->createJoint(jointInfo);
	}

	void DestroyBody(GLRigidBody* body)
	{
		this->World->destroyRigidBody(body->GetBody());

		auto itr = std::find(this->rigidBodies.begin(), this->rigidBodies.end(), body);
		if (itr != this->rigidBodies.end())
		{
			this->rigidBodies.erase(itr);
		}
	}

	reactphysics3d::PhysicsCommon PhysicsCommon;
	reactphysics3d::PhysicsWorld* World;

	GLSharedPtr<GLMeshRenderer> DebugMeshRenderer;
private:
	std::vector<GLRigidBody*> rigidBodies;
};