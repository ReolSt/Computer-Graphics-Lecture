#pragma once

#include <iostream>

#include "GL/GL.h"

#include "GMaze.h"
#include "GPlayer.h"
#include "GFrontView.h"
#include "GTopView.h"

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		int width = 0, height = 0;

		while (true)
		{
			std::cout << "Enter Maze Width, Height: ";
			std::cin >> width >> height;
			this->Maze = GCreate(GMaze, width, height);

			if (width < 5 || height < 5 || width > 30 || height > 30)
			{
				std::cout << "Invalid Maze Size." << std::endl;
				continue;
			}

			break;
		}

		auto bound = glm::max(width, height);

		this->FrontView = GCreate(GFrontView, 90.0f, -bound, bound, -bound, bound);
		this->TopView = GCreate(GTopView, 90.0f, -bound, bound, -bound, bound);
		this->Player = GCreate(GPlayer);

		this->AddChildren({ this->FrontView, this->TopView, this->Player, this->Maze });

		this->FrontView->Initialize();
		this->TopView->Initialize();
		this->Player->Initialize();
		this->Maze->Initialize();

		this->FrontView->SetOrder(1);
		this->TopView->SetOrder(2);
		this->Player->FirstPersonCamera->SetOrder(0);
		this->Player->QuaterViewCamera->SetOrder(0);

		this->SetViewMode(0);

		this->Player->Transform->SetPosition(0.0f, -5.0f, 0.0f);
	}

	void SetViewMode(int mode)
	{
		if (mode == 0)
		{
			this->Player->Deactivate();
			this->FrontView->Activate();
		}
		else if (mode == 1)
		{
			this->Player->Activate();
			this->FrontView->Deactivate();
		}

		this->ViewMode = mode;
	}

	void ToggleViewMode()
	{
		if (this->ViewMode == 0)
		{
			this->Player->Activate();
			this->FrontView->Deactivate();

			this->ViewMode = 1;
		}
		else if (this->ViewMode == 1)
		{
			this->Player->Deactivate();
			this->FrontView->Activate();

			this->ViewMode = 0;
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GWorld::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "e")
		{
			this->Player->Transform->SetPosition(-this->Maze->Width / 2.0f + 1.5f, 0.5f, -this->Maze->Height / 2.0f + 0.5f);
			this->Player->Angle.y = glm::radians(180.0f);
			this->Player->UpdatePhysics();

			this->Player->RigidBody->setIsActive(true);

			this->SetViewMode(1);
			this->Player->SetViewMode(0);
		}
		else if (key == "F1")
		{
			if (this->Scene->Physics->GetDebug())
			{
				this->Scene->Physics->SetDebug(false);
			}
			else
			{
				this->Scene->Physics->SetDebug(true);
			}
		}
		else if (key == "Tab")
		{
			ToggleViewMode();
		}
		if (key == "c" || key == "C")
		{
			this->SetViewMode(0);
			this->Scene->Physics->SetDebug(false);

			this->Maze->Initialize();
			this->Player->RigidBody->setIsActive(false);
			this->Player->Transform->SetPosition(0.0f, -5.0f, 0.0f);

			this->FrontView->Reset();
		}
		else if (key == "q" || key == "Q")
		{
			glutLeaveMainLoop();
		}
	}

	GLSharedPtr<GFrontView> FrontView;
	GLSharedPtr<GTopView> TopView;
	GLSharedPtr<GPlayer> Player;
	GLSharedPtr<GMaze> Maze;

	int ViewMode = 0;
};