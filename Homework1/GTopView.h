#pragma once

#include "GL/GL.h"

class GTopView : public GCameraController
{
public:
	GConstructor(GTopView, float fov, float left, float right, float bottom, float top)
		: GSuperClassInitializer(GCameraController, fov, left, right, bottom, top) { }

	void Initialize() override
	{
		GCameraController::Initialize();

		this->Transform->Translate(0.0f, 20.0f, 0.0f);
		this->Transform->Rotate(glm::radians(-90.0f), 0.0f, 0.0f);

		this->Perspective->SetViewportPosition(0.7f, 0.7f);
		this->Perspective->SetViewportSize(0.3f, 0.3f);

		this->Orthographic->SetViewportPosition(0.7f, 0.7f);
		this->Orthographic->SetViewportSize(0.3f, 0.3f);
	}
};