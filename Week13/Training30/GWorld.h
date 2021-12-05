#pragma once
#pragma once

#include "../GL/GL.h"

#include "Helpers.h"
#include "GCameraController.h"
#include "GPointLightController.h"
#include "GBackground.h"
#include "GTransformableObject.h"

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto cameraController = GCreate(GCameraController);
		auto lightContoller = GCreate(GPointLightController, glm::vec3(0.7f), glm::vec3(0.7f), glm::vec3(0.8f), 1.0f, 0.22f, 0.20f);

		auto background = GCreate(GBackground);
		auto axis = GCreate(GAxis3D);
		auto transformableObject = GCreate(GTransformableObject);

		this->AddChildren({ cameraController, lightContoller, axis, transformableObject });

		cameraController->Initialize();

		cameraController->AddChild(background);

		lightContoller->Initialize();
		lightContoller->GetTransform()->SetPosition(0.0f, 0.0f, 2.0f);

		background->Initialize();

		auto backgroundTransform = background->GetTransform();
		backgroundTransform->SetPosition(0.0f, 0.0f, -5.0f);
		backgroundTransform->SetLocalScale(glm::vec3(10.0f));

		axis->Initialize();
		axis->GetTransform()->SetLocalScale(glm::vec3(3.0f));

		transformableObject->Initialize();
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}
	}
};