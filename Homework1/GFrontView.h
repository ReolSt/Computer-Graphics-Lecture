#pragma once

#include "GL/GL.h"

class GFrontView : public GCameraController
{
public:
	GConstructor(GFrontView, float fov, float left, float right, float bottom, float top)
		: GSuperClassInitializer(GCameraController, fov, left, right, bottom, top) { }

	void Initialize() override
	{
		GCameraController::Initialize();

		this->Reset();
	}

	void Reset()
	{
		this->Transform->SetPosition(0.0f, 15.0f, this->Top);
		this->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->Perspective->Transform->SetEulerAngles(glm::radians(-45.0f), 0.0f, 0.0f);
		this->Orthographic->Transform->SetEulerAngles(glm::radians(-45.0f), 0.0f, 0.0f);
	}

	void Update(float deltaTime) override
	{
		GCameraController::Update(deltaTime);

		if (this->Activated)
		{
			if (this->RotationSpeed.y && this->RotationAmount.x)
			{
				this->Reset();
				this->RotationAmount.x = 0.0f;
			}
			this->Transform->RotateAround(glm::vec3(0.0f), this->RotationSpeed.y * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
			this->RotationAmount.y += this->RotationSpeed.y * deltaTime;

			if (this->RotationSpeed.x && this->RotationAmount.y)
			{
				this->Reset();
				this->RotationAmount.y = 0.0f;
			}
			this->Transform->RotateAround(glm::vec3(0.0f), this->RotationSpeed.x * deltaTime, glm::vec3(1.0f, 0.0f, 0.0f));
			this->RotationAmount.x += this->RotationSpeed.x * deltaTime;
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GCameraController::OnKeyDown(key, x, y);

		std::cout << "[GFrontView::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "x")
		{
			if (this->Activated)
			{
				this->RotationSpeed.x = 1.0f;
			}
		}
		else if (key == "X")
		{
			if (this->Activated)
			{
				this->RotationSpeed.x = -1.0f;
			}
		}
		else if (key == "y")
		{
			if (this->Activated)
			{
				this->RotationSpeed.y = 1.0f;
			}
		}
		else if (key == "Y")
		{
			if (this->Activated)
			{
				this->RotationSpeed.y = -1.0f;
			}
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GCameraController::OnKeyUp(key, x, y);

		std::cout << "[GFrontView::OnKeyUp] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "x")
		{
			this->RotationSpeed.x = 0.0f;
		}
		else if (key == "X")
		{
			this->RotationSpeed.x = 0.0f;
		}
		else if (key == "y")
		{
			this->RotationSpeed.y = 0.0f;
		}
		else if (key == "Y")
		{
			this->RotationSpeed.y = 0.0f;
		}
	}

	glm::vec3 RotationSpeed = glm::vec3(0.0f);
	glm::vec3 RotationAmount = glm::vec3(0.0f);
	glm::vec3 Angle = glm::vec3(0.0f, 0.0f, 0.0f);
};
