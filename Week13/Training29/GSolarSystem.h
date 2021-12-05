#pragma once

#include "../GL/GL.h"

#include "Helpers.h"

class GOrbitalPlanet : public GLGameObject
{
public:
	GConstructor(GOrbitalPlanet)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->planet = GCreate(GUVSphere);
		auto planetTransform = this->planet->GetTransform();

		planet->Initialize();

		planetTransform->SetLocalScale(0.3f, 0.3f, 0.3f);
		planetTransform->Translate(1.0f, 0.0f, 0.0f);

		orbitSpeed = Rand(0.5f, 2.0f);
		orbitDirection = RandSign();

		this->AddChildren({ this->planet });

		RandMaterial(planet);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();
		auto planetTransform = this->planet->GetTransform();

		glm::vec3 up(0.0f, 1.0f, 0.0f);
		up = glm::normalize(glm::rotate(transform->GetRotation(), up));

		planetTransform->RotateAround(transform->GetPosition(), deltaTime * this->orbitDirection * this->orbitSpeed, up);
	}

	void Render(const std::string& layer, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3& cameraPosition,
		const std::vector<GLSharedPtr<GLLight>>& lights) override
	{
		GLGameObject::Render(layer, viewMatrix, projectionMatrix, cameraPosition, lights);
	}

private:
	int orbitDirection = 1;
	float orbitSpeed = 1.0f;

	GLSharedPtr<GLGameObject> planet;
};

class GSolarSystem : public GLGameObject
{
public:
	GConstructor(GSolarSystem)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto orbitalPlanetA = GCreate(GOrbitalPlanet);
		auto orbitalPlanetB = GCreate(GOrbitalPlanet);
		auto orbitalPlanetC = GCreate(GOrbitalPlanet);

		this->AddChildren({ orbitalPlanetA, orbitalPlanetB, orbitalPlanetC });

		orbitalPlanetA->Initialize();
		orbitalPlanetB->Initialize();
		orbitalPlanetC->Initialize();

		orbitalPlanetB->GetTransform()->Rotate(0.0f, 0.0f, glm::radians(45.0f));
		orbitalPlanetC->GetTransform()->Rotate(0.0f, 0.0f, glm::radians(-45.0f));
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "m")
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
		}
		else if (key == "M")
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	int rotationDirection = 0;
};