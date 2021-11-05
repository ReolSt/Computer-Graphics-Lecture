#pragma once

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <ctime>
#include <chrono>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLGameObject.h"
#include "GLCamera.h"
#include "GLPhysics.h"

class GLScene
{
public:
	GLScene(const std::string& name)
		: Name(name),
		  Background(1.0f, 1.0f, 1.0f)
	{
		this->Root = GCreate(GLGameObject);
		this->Root->Scene = GLSharedPtr<GLScene>(this);

		this->Physics = GLCreate<GLPhysics>();
	}

	virtual ~GLScene() { }

	void AddCamera(const GLSharedPtr<GCamera>& camera)
	{
		assert(camera != nullptr);

		this->Cameras.push_back(camera);
	}

	void RemoveCamera(const GLSharedPtr<GCamera>& camera)
	{
		assert(camera != nullptr);
		
		auto position = std::find(this->Cameras.begin(), this->Cameras.end(), camera);

		if (position != this->Cameras.end())
		{
			this->Cameras.erase(position);
		}
	}

	void Update(float deltaTime)
	{
		this->Root->Update(deltaTime);
	}

	void Render(const glm::vec2& windowSize)
	{
		for (auto& camera : this->Cameras)
		{
			if (camera->IsActive())
			{
				auto cameraViewportPosition = camera->GetViewportPosition();
				auto cameraViewportSize = camera->GetViewportSize();

				int x = cameraViewportPosition.x * windowSize.x;
				int y = cameraViewportPosition.y * windowSize.y;

				int width = cameraViewportSize.x * windowSize.x;
				int height = cameraViewportSize.y * windowSize.y;

				glViewport(x, y, width, height);

				this->Root->Render(camera->GetLayer(), camera->GetCameraMatrix());
			}
		}
	}

	GLSharedPtr<GLGameObject> Root;
    std::vector<GLSharedPtr<GCamera>> Cameras;

	std::string Name;

	GLColor Background;
};