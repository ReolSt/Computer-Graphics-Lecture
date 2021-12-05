#pragma once

#include "../GL/GL.h"

#include "Helpers.h"
#include "GCameraController.h"
#include "GPointLightController.h"
#include "GFloor.h"
#include "GSolarSystem.h"
#include "GFractalPhyramid.h"
#include "GSnowFallEffect.h"
#include "GTransparentCube.h"

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		auto cameraController = GCreate(GCameraController);
		auto lightContoller = GCreate(GPointLightController, glm::vec3(0.7f), glm::vec3(0.7f), glm::vec3(0.8f), 1.0f, 0.22f, 0.20f);

		auto floor = GCreate(GFloor);
		auto solarSystem = GCreate(GSolarSystem);
		auto fractalPhyramid = GCreate(GFractalPhyramid);

		auto snowFallEffect = GCreate(GSnowFallEffect);

		this->AddChildren({ cameraController, lightContoller, floor, solarSystem, fractalPhyramid, snowFallEffect });

		cameraController->Initialize();
		lightContoller->Initialize();
		floor->Initialize();
		solarSystem->Initialize();
		fractalPhyramid->Initialize();
		snowFallEffect->Initialize();

		lightContoller->GetTransform()->SetPosition(0.0f, 1.0f, 2.0f);
		solarSystem->GetTransform()->SetPosition(0.0f, 1.0f, 0.0f);
		fractalPhyramid->GetTransform()->SetPosition(0.0f, 1.0f, 0.0f);

		for (int i = 0; i <= 4; ++i)
		{
			auto cubeA = GCreate(GTransparentCube);
			auto cubeB = GCreate(GTransparentCube);

			this->AddChildren({ cubeA, cubeB });

			cubeA->Initialize();
			cubeB->Initialize();

			auto transformA = cubeA->GetTransform();
			auto transformB = cubeB->GetTransform();
			
			transformA->SetPosition(-2.0f + i * 4.0f / 4, 0.5f, -1.0f);
			transformB->SetPosition(-2.0f + i * 4.0f / 4, 0.5f, 1.0f);

			transformA->SetScale(0.5f, 1.0f, 0.5f);
			transformB->SetScale(0.5f, 1.0f, 0.5f);
		}
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