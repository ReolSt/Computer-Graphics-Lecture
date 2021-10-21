#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GL.h"

void ToggleDirection(int& direction, int T)
{
	direction = direction == T ? 0 : T;
}

void OffDirection(int& direction, int T)
{
	direction = direction == T ? 0 : direction;
}

class GOrbitalMoon : public GLGameObject
{
public:
	GConstructor(GOrbitalMoon)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Moon = GCreate(GUVSphere);
		this->Moon->Transform->SetLocalScale(0.3f, 0.3f, 0.3f);
		this->Moon->Transform->LocalPosition.x += 1.0f;
		SetVertexColor(this->Moon, RandColor3f());

		this->OrbitalLine = GCreate(GLineCircle);
		this->OrbitalLine->Transform->SetLocalScale(2.0f, 2.0f, 2.0f);
		this->OrbitalLine->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->OrbitSpeed = Rand(0.5f, 2.0f);
		this->OrbitDirection = RandSign();

		this->AddChildren({ this->Moon, this->OrbitalLine });
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		OrbitAmount += deltaTime * this->OrbitDirection * this->OrbitSpeed;
		this->Transform->SetEulerAngles(0.0f, OrbitAmount, 0.0f);
	}

	GLSharedPtr<GUVSphere> Moon;
	GLSharedPtr<GLineCircle> OrbitalLine;

	int OrbitDirection = 1;
	float OrbitSpeed = 1.0f;

	float OrbitAmount = 0.0f;
};

class GOrbitalPlanet : public GLGameObject
{
public:
	GConstructor(GOrbitalPlanet)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Planet = GCreate(GUVSphere);
		this->Planet->Transform->SetLocalScale(0.3f, 0.3f, 0.3f);
		this->Planet->Transform->LocalPosition.x += 1.0f;
		SetVertexColor(this->Planet, RandColor3f());

		this->OrbitalLine = GCreate(GLineCircle);
		this->OrbitalLine->Transform->SetLocalScale(2.0f, 2.0f, 2.0f);
		this->OrbitalLine->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->Moon = GCreate(GOrbitalMoon);

		this->OrbitSpeed = Rand(0.5f, 2.0f);
		this->OrbitDirection = RandSign();

		this->AddChildren({ this->Planet, this->OrbitalLine });

		this->Planet->AddChild(this->Moon);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Transform->Rotate(0.0f, deltaTime * this->OrbitDirection * this->OrbitSpeed, 0.0f);
	}

	GLSharedPtr<GUVSphere> Planet;
	GLSharedPtr<GLineCircle> OrbitalLine;
	GLSharedPtr<GOrbitalMoon> Moon;

	int OrbitDirection = 1;
	float OrbitSpeed = 1.0f;
};

class GSolarSystem : public GLGameObject
{
public:
	GConstructor(GSolarSystem)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Solar = GCreate(GUVSphere);
		this->Solar->Transform->SetLocalScale(0.6f, 0.6f, 0.6f);
		SetVertexColor(this->Solar, GLColor(1.0f, 1.0f, 0.0f));

		this->OrbitalPlanetA = GCreate(GOrbitalPlanet);
		this->OrbitalPlanetB = GCreate(GOrbitalPlanet);
		this->OrbitalPlanetC = GCreate(GOrbitalPlanet);

		this->OrbitalPlanetB->Transform->Rotate(0.0f, 0.0f, glm::radians(45.0f));
		this->OrbitalPlanetB->Moon->Transform->Rotate(0.0f, 0.0f, glm::radians(-45.0f));

		this->OrbitalPlanetC->Transform->Rotate(0.0f, 0.0f, glm::radians(-45.0f));
		this->OrbitalPlanetC->Moon->Transform->Rotate(0.0f, 0.0f, glm::radians(45.0f));

		this->AddChildren({ this->Solar, this->OrbitalPlanetA, this->OrbitalPlanetB, this->OrbitalPlanetC });
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Transform->Translate(
			this->TranslationDirection.x * deltaTime,
			this->TranslationDirection.y * deltaTime,
			this->TranslationDirection.z * deltaTime
		);

		this->Transform->Rotate(0.0f, this->RotationDirection * deltaTime, 0.0f);
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
		else if (key == "w")
		{
			this->TranslationDirection.y = 1;
		}
		else if (key == "a")
		{
			this->TranslationDirection.x = -1;
		}
		else if (key == "s")
		{
			this->TranslationDirection.y = -1;
		}
		else if (key == "d")
		{
			this->TranslationDirection.x = 1;
		}
		else if (key == "z")
		{
			this->TranslationDirection.z = 1;
		}
		else if (key == "x")
		{
			this->TranslationDirection.z = -1;
		}
		else if (key == "y")
		{
			ToggleDirection(this->RotationDirection, 1);
		}
		else if (key == "Y")
		{
			ToggleDirection(this->RotationDirection, -1);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "w")
		{
			OffDirection(this->TranslationDirection.y, 1);
		}
		else if (key == "a")
		{
			OffDirection(this->TranslationDirection.x, -1);
		}
		else if (key == "s")
		{
			OffDirection(this->TranslationDirection.y, -1);
		}
		else if (key == "d")
		{
			OffDirection(this->TranslationDirection.x, 1);
		}
		else if (key == "z")
		{
			OffDirection(this->TranslationDirection.z, 1);
		}
		else if (key == "x")
		{
			OffDirection(this->TranslationDirection.z, -1);
		}
	}
	GLSharedPtr<GUVSphere> Solar;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetA;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetB;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetC;

	glm::tvec3<int> TranslationDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	int RotationDirection = 0;
};

class GSolarSystemDisplayer : public GLGameObject
{
public:
	GConstructor(GSolarSystemDisplayer)
		: GSuperClassInitializer(GLGameObject)
	{
		this->PerspectiveCamera = GCreate(GPerspectiveCamera, 90.0f);
		this->OrthographicCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);

		this->Scene->Root->AddChildren({ this->PerspectiveCamera, this->OrthographicCamera });

		this->Scene->AddCamera(this->PerspectiveCamera);
		this->Scene->AddCamera(this->OrthographicCamera);

		this->OrthographicCamera->SetActive(false);

		this->PerspectiveCamera->Transform->Translate(0.0f, 0.5f, 2.0f);
		this->PerspectiveCamera->Transform->Rotate(glm::radians(-20.0f), 0.0f, 0.0f);

		this->OrthographicCamera->Transform->Translate(0.0f, 0.5f, 2.0f);
		this->OrthographicCamera->Transform->Rotate(glm::radians(-20.0f), 0.0f, 0.0f);

		this->SolarSystem = GCreate(GSolarSystem);
		this->AddChild(this->SolarSystem);
	}

	void OnKeyDown(const std::string& key, int x, int y)
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "p")
		{
			this->PerspectiveCamera->SetActive(true);
			this->OrthographicCamera->SetActive(false);
		}
		else if (key == "P")
		{
			this->PerspectiveCamera->SetActive(false);
			this->OrthographicCamera->SetActive(true);
		}
	}

	GLSharedPtr<GPerspectiveCamera> PerspectiveCamera;
	GLSharedPtr<GOrthographicCamera> OrthographicCamera;

	GLSharedPtr<GSolarSystem> SolarSystem;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training18"));

	InitializeGLEW();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	auto scene = GLCreate<GLScene>("Training18");
	scene->Background = GLColor(0.0f, 0.0f, 0.0f);

	GCreateAndAddChildFor(scene->Root, GSolarSystemDisplayer);

	GLLoadScene(scene);

	glutMainLoop();
}