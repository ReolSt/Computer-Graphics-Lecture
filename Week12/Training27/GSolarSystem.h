#pragma once

#include "../GL/GL.h"

#include "Helpers.h"

class GOrbitalMoon : public GLGameObject
{
public:
	GConstructor(GOrbitalMoon)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto shape = GCreate(GUVSphere);
		auto orbitalLine = GCreate(GLineCircle);

		this->AddChildren({ shape, orbitalLine });
		
		shape->Initialize();
		orbitalLine->Initialize();

		auto shapeTransform = shape->GetTransform();
		shapeTransform->SetLocalScale(0.3f, 0.3f, 0.3f);
		shapeTransform->LocalPosition.x += 1.0f;
		RandMaterial(shape);

		auto orbitalLineTransform = orbitalLine->GetTransform();
		orbitalLineTransform->SetLocalScale(2.0f, 2.0f, 2.0f);
		orbitalLineTransform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		
		orbitSpeed = Rand(0.5f, 2.0f);
		orbitDirection = RandSign();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	int orbitDirection = 1;
	float orbitSpeed = 1.0f;

	float orbitAmount = 0.0f;
};

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

		auto planet = GCreate(GUVSphere);
		auto planetTransform = planet->GetTransform();

		planetTransform->SetLocalScale(0.3f, 0.3f, 0.3f);
		planetTransform->LocalPosition.x += 1.0f;

		auto orbitalLine = GCreate(GLineCircle);
		auto orbitalLineTransform = orbitalLine->GetTransform();

		orbitalLineTransform->SetLocalScale(2.0f, 2.0f, 2.0f);
		orbitalLineTransform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		orbitSpeed = Rand(0.5f, 2.0f);
		orbitDirection = RandSign();

		this->AddChildren({ planet, orbitalLine });

		planet->Initialize();
		orbitalLine->Initialize();

		RandMaterial(planet);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		auto transform = this->GetTransform();

		glm::vec3 up(0.0f, 1.0f, 0.0f);
		up = glm::normalize(glm::rotate(transform->GetRotation(), up));

		transform->Rotate(deltaTime * this->orbitDirection * this->orbitSpeed, up);
	}

	int orbitDirection = 1;
	float orbitSpeed = 1.0f;
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

		this->GetTransform()->Rotate(0.0f, this->rotationDirection * deltaTime, 0.0f);
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
		else if (key == "y")
		{
			ToggleDirection(this->rotationDirection, 1);
		}
		else if (key == "Y")
		{
			ToggleDirection(this->rotationDirection, -1);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	int rotationDirection = 0;
};