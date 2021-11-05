#pragma once

#include <vector>

#include "GL/GL.h"

#include "GMazeWall.h"
#include "GFloor.h"

class GMaze : public GLGameObject
{
public:
	GConstructor(GMaze, int width = 20, int height = 20)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Width = width;
		this->Height = height;
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Map.clear();
		this->Walls.clear();

		for (auto y = 0; y < this->Height; ++y)
		{
			this->Map.push_back(std::vector<bool>());
			this->Walls.push_back(std::vector<GLSharedPtr<GMazeWall>>());
			for (auto x = 0; x < this->Width; ++x)
			{
				this->Map[y].push_back(false);
				this->Walls[y].push_back(nullptr);
			}
		}

		this->SetupMesh();
	}

	void CreateWall(int x, int y)
	{
		auto wall = GCreate(GMazeWall);
		this->AddChild(wall);

		wall->Initialize();

		wall->Transform->LocalPosition.x = x - this->Width / 2.0f + 0.5f;
		wall->Transform->LocalPosition.z = y - this->Height / 2.0f + 0.5f;

		wall->UpdatePhysics();

		GLColor wallColor;
		wallColor.Rand3f();
		SetVertexColor(wall->MeshObject, wallColor);

		this->Walls[y][x] = wall;
	}

	void SetupMesh()
	{
		this->ClearChildren();

		auto floor = GCreate(GFloor);
		this->AddChild(floor);

		floor->Initialize();

		floor->Transform->SetLocalScale(this->Width, this->Height, 0.0f);
		floor->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		floor->Transform->Translate(0.0f, -0.001f, 0.0f);
		SetVertexColor(floor, GLColor(0.3f, 0.3f, 0.3f));

		floor->UpdatePhysics();

		for (auto y = 0; y < this->Height; ++y)
		{
			for (auto x = 0; x < this->Width; ++x)
			{
				if (!this->Map[y][x])
				{
					this->CreateWall(x, y);
				}
			}
		}
	}

	void ActivateWall(int x, int y)
	{
		this->Map[y][x] = false;
		if (this->Walls[y][x] == nullptr)
		{
			this->CreateWall(x, y);
		}
	}

	void DeactivateWall(int x, int y)
	{
		this->Map[y][x] = true;
		if (this->Walls[y][x] != nullptr)
		{
			this->RemoveChild(this->Walls[y][x]);
			this->Walls[y][x] = nullptr;
		}
	}

	void Generate()
	{
		this->DeactivateWall(1, 0);
		this->DeactivateWall(this->Width - 2, this->Height - 1);
		for (auto y = 0; y < this->Height - 1; ++y)
		{
			int count = 1;
			for (auto x = 0; x < this->Width - 1; ++x)
			{
				if (x == this->Width - 2 && y == this->Height - 2)
				{
					continue;
				}

				if (x == this->Width - 2)
				{
					this->DeactivateWall(x, y + 1);

					continue;
				}

				if (y == this->Height - 2)
				{
					this->DeactivateWall(x + 1, y);

					continue;
				}

				if (x % 2 == 0 || y % 2 == 0)
				{
					continue;
				}

				this->DeactivateWall(x, y);

				if (Rand(0, 1) == 0)
				{
					this->DeactivateWall(x + 1, y);
					++count;
				}
				else
				{
					int randomIndex = Rand(0, count - 1);
					this->DeactivateWall(x - randomIndex * 2, y + 1);
					count = 1;
				}
			}
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << "[GMaze::OnKeyDown] key=" << key << " x=" << x << " y=" << y << std::endl;

		if (key == "r")
		{
			this->Generate();
		}
	}

	std::vector<std::vector<bool>> Map;
	std::vector<std::vector<GLSharedPtr<GMazeWall>>> Walls;

	int Width;
	int Height;
};