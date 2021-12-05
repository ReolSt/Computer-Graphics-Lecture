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
#include "GRobot.h"
#include "GObstacle.h"
#include "GTransformer.h"

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		this->Reset();
	}

	void Reset()
	{
		this->ClearChildren();

		auto cameraController = GCreate(GCameraController);
		auto lightContoller = GCreate(GPointLightController, glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 1.0f, 0.22f, 0.2f);

		auto floor = GCreate(GFloor);
		auto robot = GCreate(GRobot);

		this->AddChildren({ cameraController, lightContoller, floor, robot });

		cameraController->Initialize();
		lightContoller->Initialize();
		floor->Initialize();
		robot->Initialize();

		lightContoller->GetTransform()->SetPosition(0.0f, 2.0f, 0.0f);

		floor->RemapTexture();
		floor->UpdateBody();

		robot->GetTransform()->SetPosition(0.0f, 1.0f, 0.0f);
		robot->UpdateBody();

		for (int i = 0; i < 10; ++i)
		{
			auto obstacle = GCreate(GObstacle);

			this->AddChild(obstacle);

			obstacle->Initialize();
			obstacle->GetTransform()->SetPosition(Rand3v(-4.0f, 4.0f, 1.0f, 1.0f, -4.0f, 4.0f));
			obstacle->UpdateBody();

			RandMaterial(obstacle);
		}

		for (int i = 0; i < 10; ++i)
		{
			auto transformer = GCreate(GTransformer);

			this->AddChild(transformer);

			transformer->Initialize();
			transformer->GetTransform()->SetPosition(Rand3v(-4.0f, 4.0f, 1.0f, 1.0f, -4.0f, 4.0f));
			transformer->cube->UpdateBody();
			transformer->SetRobot(robot);

			RandMaterial(transformer);
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "c")
		{
			this->Reset();
		}
		else if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}
	}
};