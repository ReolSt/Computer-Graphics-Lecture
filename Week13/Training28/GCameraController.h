#pragma once

#include "../GL/GL.h"

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		this->perspectiveCamera = GCreate(GPerspectiveCamera, 90.0f);
		this->orthographicCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);

		auto scene = this->GetScene();
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
			glm::vec3(0.0f, 0.0f, 0.0f), deltaTime * this->rotatingAroundCenter, glm::vec3(0.0f, 1.0f, 0.0f));

		transform->Rotate(deltaTime * this->rotating, glm::vec3(0.0f, 1.0f, 0.0f));

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
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
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

		this->GetTransform()->SetPosition(0.0f, 2.0f, 2.5f);
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