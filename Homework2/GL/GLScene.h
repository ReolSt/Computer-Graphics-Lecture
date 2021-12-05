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
#include "GLLight.h"
#include "GLPhysics.h"

class GLScene
{
public:
	GLScene(const std::string& name)
		: name(name),
		  background(1.0f, 1.0f, 1.0f)
	{
		this->root = GCreate(GLGameObject);
		this->root->SetScene(GLSharedPtr<GLScene>(this));

		this->physics = GLCreate<GLPhysics>();
	}

	virtual ~GLScene() { }

	void AddCamera(const GLSharedPtr<GCamera>& camera)
	{
		assert(camera != nullptr);

		this->cameras.push_back(camera);
	}

	void RemoveCamera(const GLSharedPtr<GCamera>& camera)
	{
		assert(camera != nullptr);
		
		auto position = std::find(this->cameras.begin(), this->cameras.end(), camera);

		if (position != this->cameras.end())
		{
			this->cameras.erase(position);
		}
	}

	void AddLight(const GLSharedPtr<GLLight>& light)
	{
		assert(light != nullptr);

		this->lights.push_back(light);
	}

	void RemoveLight(const GLSharedPtr<GLLight>& light)
	{
		assert(light != nullptr);

		auto position = std::find(this->lights.begin(), this->lights.end(), light);

		if (position != this->lights.end())
		{
			this->lights.erase(position);
		}
	}

	void Update(float deltaTime)
	{
		this->timeStepAccumulator += deltaTime;

		while (this->timeStepAccumulator >= this->fixedTimeStep)
		{
			this->root->Update(this->fixedTimeStep);
			this->physics->Update(this->fixedTimeStep);

			this->timeStepAccumulator -= this->fixedTimeStep;
		}
	}

	void Render(const glm::vec2& windowSize)
	{
		std::sort(this->cameras.begin(), this->cameras.end(),
			[](const GLSharedPtr<GCamera>& a, const GLSharedPtr<GCamera>& b)
			{
				return a->GetOrder() < b->GetOrder();
			}
		);

		auto backgroundColor = this->GetBackgroudColor();

		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (const auto& camera : this->cameras)
		{
			if (camera->IsActive())
			{
			    camera->UpdateMatrices();

				auto cameraViewportPosition = camera->GetViewportPosition();
				auto cameraViewportSize = camera->GetViewportSize();

				int x = cameraViewportPosition.x * windowSize.x;
				int y = cameraViewportPosition.y * windowSize.y;

				int width = cameraViewportSize.x * windowSize.x;
				int height = cameraViewportSize.y * windowSize.y;

				glViewport(x, y, width, height);
				glClear(GL_DEPTH_BUFFER_BIT);

				glm::vec3 cameraPosition = camera->GetTransform()->GetPosition();

				this->root->Render(camera->GetLayer(), camera->GetCachedViewMatrix(), camera->GetCachedProjectionMatrix(), cameraPosition, this->lights);
				this->physics->Render(camera->GetCachedViewMatrix(), camera->GetCachedProjectionMatrix(), cameraPosition);
			}
		}

		glutSwapBuffers();
	}

	void SetBackgroundColor(const GLColor& color)
	{
		this->background = color;
	}

	GLColor GetBackgroudColor()
	{
		return this->background;
	}

	GLSharedPtr<GLPhysics> GetPhysics()
	{
		return this->physics;
	}

	GLSharedPtr<GLGameObject> GetRoot()
	{
		return this->root;
	}

	std::vector<GLSharedPtr<GCamera>>& GetCameras()
	{
		return this->cameras;
	}

	std::vector<GLSharedPtr<GLLight>>& GetLights()
	{
		return this->lights;
	}

protected:
	GLSharedPtr<GLPhysics> physics;
	GLSharedPtr<GLGameObject> root;
	std::vector<GLSharedPtr<GCamera>> cameras;
	std::vector<GLSharedPtr<GLLight>> lights;

	std::string name;
	GLColor background;

	float fixedTimeStep = 0.02f;
	float timeStepAccumulator = 0.0f;
};