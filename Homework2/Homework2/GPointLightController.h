#pragma once

#include "../GL/GL.h"

#include "Helpers.h"

class GPointLightController : public GLGameObject
{
public:
	GConstructor(GPointLightController, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: GSuperClassInitializer(GLGameObject)
	{
		this->light = GLCreate<GLPointLight>();

		this->light->SetAmbient(ambient);
		this->light->SetDiffuse(diffuse);
		this->light->SetSpecular(specular);
		this->light->SetConstant(constant);
		this->light->SetLinear(linear);
		this->light->SetQuadratic(quadratic);
	}

	~GPointLightController()
	{
		GLGetCurrentScene()->RemoveLight(this->light);
	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		GLGetCurrentScene()->AddLight(this->light);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);
		
		if (key == "-" || key == "_")
		{
			this->light->SetAmbient(this->light->GetAmbient() - 0.1f);
			this->light->SetDiffuse(this->light->GetDiffuse() - 0.1f);
			this->light->SetSpecular(this->light->GetSpecular() - 0.1f);
		}
		else if (key == "+" || key == "=")
		{
			this->light->SetAmbient(this->light->GetAmbient() + 0.1f);
			this->light->SetDiffuse(this->light->GetDiffuse() + 0.1f);
			this->light->SetSpecular(this->light->GetSpecular() + 0.1f);
		}
		else if (key == "t")
		{
			this->light->SetActive(true);
		}
		else if (key == "T")
		{
			this->light->SetActive(false);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		this->light->SetPosition(transform->GetPosition());

		glm::vec3 back = glm::normalize(transform->GetRotation() * glm::vec3(0.0f, 0.0f, 1.0f));

		transform->Translate(this->moveSpeed.z * deltaTime * back);

		if (this->rotationDirection)
		{
			transform->RotateAround(glm::vec3(0.0f), deltaTime * this->rotationDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		}
	}

private:
	GLSharedPtr<GLPointLight> light;

	glm::vec3 moveSpeed = glm::vec3(0.0f);
	int rotationDirection = 0;
};