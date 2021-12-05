#pragma once

#include "../GL/GL.h"

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	virtual ~GCameraController()
	{
		GLGetCurrentScene()->RemoveCamera(this->perspectiveCamera);
		GLGetCurrentScene()->RemoveCamera(this->orthographicCamera);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->perspectiveCamera = GCreate(GPerspectiveCamera, 90.0f);
		this->orthographicCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);

		auto scene = GLGetCurrentScene();
		scene->AddCamera(this->perspectiveCamera);
		scene->AddCamera(this->orthographicCamera);

		this->AddChildren({ this->perspectiveCamera, this->orthographicCamera });

		this->Reset();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		transform->RotateAround(
			glm::vec3(0.0f), deltaTime * this->rotatingAroundCenter, glm::vec3(0.0f, 1.0f, 0.0f));

		transform->Translate(glm::vec3(this->directions) * deltaTime);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "p")
		{
			this->perspectiveCamera->SetActive(true);
			this->orthographicCamera->SetActive(false);
		}
		else if (key == "P")
		{
			this->perspectiveCamera->SetActive(false);
			this->orthographicCamera->SetActive(true);
		}
		else if (key == "w")
		{
			this->directions.z = -1;
		}
		else if (key == "a")
		{
			this->directions.x = -1;
		}
		else if (key == "s")
		{
			this->directions.z = 1;
		}
		else if (key == "d")
		{
			this->directions.x = 1;
		}
		else if (key == "r")
		{
			ToggleDirection(this->rotatingAroundCenter, 1);
		}
		else if (key == "R")
		{
			ToggleDirection(this->rotatingAroundCenter, -1);
		}
		else if (key == "c")
		{
			this->Reset();
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "w")
		{
			OffDirection(this->directions.z, -1);
		}
		else if (key == "a")
		{
			OffDirection(this->directions.x, -1);
		}
		else if (key == "s")
		{
			OffDirection(this->directions.z, 1);
		}
		else if (key == "d")
		{
			OffDirection(this->directions.x, 1);
		}
	}

	void Stop()
	{
		this->rotating = 0;
		this->rotatingAroundCenter = 0;
		this->directions = glm::tvec3<int>(0);
	}

	void Reset()
	{
		this->perspectiveCamera->SetActive(true);
		this->orthographicCamera->SetActive(false);

		this->GetTransform()->SetPosition(0.0f, 4.0f, 4.0f);
		this->perspectiveCamera->GetTransform()->SetEulerAngles(glm::radians(-30.0f), 0.0f, 0.0f);
		this->orthographicCamera->GetTransform()->SetEulerAngles(glm::radians(-30.0f), 0.0f, 0.0f);
	}

private:
	int rotatingAroundCenter = 0;
	int rotating = 0;

	glm::tvec3<int> directions = glm::tvec3<int>(0);

	GLSharedPtr<GPerspectiveCamera> perspectiveCamera;
	GLSharedPtr<GOrthographicCamera> orthographicCamera;
};