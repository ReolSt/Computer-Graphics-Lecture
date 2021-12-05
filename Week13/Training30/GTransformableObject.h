#pragma once

#include "../GL/GL.h"
#include "GTextureObjects.h"

class GTransformableObject : public GLGameObject
{
public:
	GConstructor(GTransformableObject)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		this->cube = GCreate(GTextureCube);
		this->pyramid = GCreate(GTexturePyramid);

		this->AddChildren({ this->cube, this->pyramid });

		this->cube->Initialize();
		this->pyramid->Initialize();

		this->GetTransform()->Rotate(0.0f, glm::radians(-30.0f), 0.0f);

		this->cube->SetVisible(true);
		this->pyramid->SetVisible(false);
	}

	void Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->GetTransform()->Translate(this->moveSpeed * deltaTime);
		this->GetTransform()->Rotate(this->rotationSpeed * deltaTime);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		if (key == "c")
		{
			this->cube->SetVisible(true);
			this->pyramid->SetVisible(false);
		}
		else if (key == "p")
		{
			this->cube->SetVisible(false);
			this->pyramid->SetVisible(true);
		}
		else if (key == "h")
		{
			if (glIsEnabled(GL_DEPTH_TEST))
			{
				glDisable(GL_DEPTH_TEST);
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
			}
		}
		else if (key == "Left")
		{
			this->moveSpeed.x = this->moveSpeed.x = -1;
		}
		else if (key == "Right")
		{
			this->moveSpeed.x = this->moveSpeed.x = 1;
		}
		else if (key == "Down")
		{
			this->moveSpeed.y = this->moveSpeed.y = -1;
		}
		else if (key == "Up")
		{
			this->moveSpeed.y = this->moveSpeed.y = 1;
		}
		else if (key == "x")
		{
			this->rotationSpeed.x = this->rotationSpeed.x != 1 ? 1 : 0;
		}
		else if (key == "X")
		{
			this->rotationSpeed.x = this->rotationSpeed.x != -1 ? -1 : 0;
		}
		else if (key == "y")
		{
			this->rotationSpeed.y = this->rotationSpeed.y != 1 ? 1 : 0;
		}
		else if (key == "Y")
		{
			this->rotationSpeed.y = this->rotationSpeed.y != -1 ? -1 : 0;
		}
		else if (key == "z")
		{
			this->rotationSpeed.z = this->rotationSpeed.z != 1 ? 1 : 0;
		}
		else if (key == "Z")
		{
			this->rotationSpeed.z = this->rotationSpeed.z != -1 ? -1 : 0;
		}
		else if (key == "w")
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (key == "W")
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else if (key == "s")
		{
			this->GetTransform()->SetLocalPosition(0.0f, 0.0f, 0.0f);
			this->GetTransform()->SetLocalEulerAngles(0.0f, glm::radians(-30.0f), 0.0f);

			this->moveSpeed = glm::vec3(0.0f);
			this->rotationSpeed = glm::vec3(0.0f);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		if (key == "Up")
		{
			this->moveSpeed.y = 0.0f;
		}
		else if (key == "Down")
		{
			this->moveSpeed.y = 0.0f;
		}
		else if (key == "Left")
		{
			this->moveSpeed.x = 0.0f;
		}
		else if (key == "Right")
		{
			this->moveSpeed.x = 0.0f;
		}
	}

	glm::vec3 moveSpeed = glm::vec3(0.0f);
	glm::vec3 rotationSpeed = glm::vec3(0.0f);

	GLSharedPtr<GLGameObject> cube;
	GLSharedPtr<GLGameObject> pyramid;
};