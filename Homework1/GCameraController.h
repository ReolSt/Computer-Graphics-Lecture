#pragma once

#include "GL/GL.h"

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController, float fov = 90.0f, float left = -5.0f, float right = 5.0f, float bottom = -5.0f, float top = 5.0f)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Fov = fov;
		this->Left = left;
		this->Right = right;
		this->Bottom = bottom;
		this->Top = top;
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Perspective = GCreateChild(GPerspectiveCamera, Fov);
		this->Orthographic = GCreateChild(GOrthographicCamera, Left, Right, Bottom, Top);

		this->AddChildren({ this->Perspective, this->Orthographic });
		this->Scene->AddCamera(this->Perspective);
		this->Scene->AddCamera(this->Orthographic);

		this->Activate();
	}

	void SetOrder(int order)
	{
		this->Perspective->SetOrder(order);
		this->Orthographic->SetOrder(order);
	}

	int GetOrder()
	{
		return this->Perspective->GetOrder();
	}

	void Activate()
	{
		this->Activated = true;

		this->Perspective->SetActive(this->State == 0);
		this->Orthographic->SetActive(this->State == 1);
	}

	void Deactivate()
	{
		this->Activated = false;

		this->Perspective->SetActive(false);
		this->Orthographic->SetActive(false);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GCameraController::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "p")
		{
			this->State = 0;
		}
		else if (key == "o")
		{
			this->State = 1;
		}

		if (this->Activated)
		{
			this->Activate();
		}
	}

	GLSharedPtr<GPerspectiveCamera> Perspective;
	GLSharedPtr<GOrthographicCamera> Orthographic;

	int State = 0;
	int Activated = true;

	float Fov = 0.0f;
	float Left = 0.0f;
	float Right = 0.0f;
	float Bottom = 0.0f;
	float Top = 0.0f;
};
