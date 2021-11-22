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

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Shape = GCreate(GUVSphere);
		this->OrbitalLine = GCreate(GLineCircle);
		this->AddChildren({ this->Shape, this->OrbitalLine });

		this->Shape->Initialize();
		this->OrbitalLine->Initialize();

		this->Shape->Transform->SetLocalScale(0.3f, 0.3f, 0.3f);
		this->Shape->Transform->LocalPosition.x += 1.0f;
		RandMaterial(this->Shape);

		this->OrbitalLine->Transform->SetLocalScale(2.0f, 2.0f, 2.0f);
		this->OrbitalLine->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->OrbitSpeed = Rand(0.5f, 2.0f);
		this->OrbitDirection = RandSign();

	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	GLSharedPtr<GUVSphere> Shape;
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

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Planet = GCreate(GUVSphere);
		this->AddChildren({ this->Planet });

		this->Moon = GCreate(GOrbitalMoon);
		this->Planet->AddChild(this->Moon);

		this->Planet->Initialize();
		this->Moon->Initialize();

		this->Planet->Transform->SetLocalScale(0.3f, 0.3f, 0.3f);
		this->Planet->Transform->LocalPosition.x += 1.0f;
		RandMaterial(this->Planet);

		this->OrbitSpeed = Rand(0.5f, 2.0f);
		this->OrbitDirection = RandSign();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);
	}

	GLSharedPtr<GUVSphere> Planet;
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

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->Solar = GCreate(GUVSphere);
		this->Solar->Transform->SetLocalScale(0.6f, 0.6f, 0.6f);

		auto solarMaterial = this->Solar->MeshRenderer->GetMaterial();
		solarMaterial->SetVector("ambient", glm::vec3(0.24725f, 0.1995f, 0.0745f));
		solarMaterial->SetVector("diffuse", glm::vec3(0.75164f, 0.60648f, 0.22648f));
		solarMaterial->SetVector("specular", glm::vec3(0.62828f, 0.5558f, 0.36606f));
		solarMaterial->SetFloat("shininess", 128.0f);

		this->OrbitalPlanetA = GCreate(GOrbitalPlanet);
		this->OrbitalPlanetB = GCreate(GOrbitalPlanet);
		this->OrbitalPlanetC = GCreate(GOrbitalPlanet);

		this->AddChildren({ this->Solar, this->OrbitalPlanetA, this->OrbitalPlanetB, this->OrbitalPlanetC });

		this->OrbitalPlanetA->Initialize();
		this->OrbitalPlanetB->Initialize();
		this->OrbitalPlanetC->Initialize();

		this->OrbitalPlanetB->Transform->Rotate(0.0f, 0.0f, glm::radians(45.0f));
		this->OrbitalPlanetB->Moon->Transform->Rotate(0.0f, 0.0f, glm::radians(-45.0f));

		this->OrbitalPlanetC->Transform->Rotate(0.0f, 0.0f, glm::radians(-45.0f));
		this->OrbitalPlanetC->Moon->Transform->Rotate(0.0f, 0.0f, glm::radians(45.0f));
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

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
	}

	GLSharedPtr<GUVSphere> Solar;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetA;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetB;
	GLSharedPtr<GOrbitalPlanet> OrbitalPlanetC;

	int RotationDirection = 0;
};

class GPointLightObject : public GCube
{
public:
	GConstructor(GPointLightObject, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
		float constant, float linear, float quadratic)
		: GSuperClassInitializer(GCube)
	{
		this->Light = GLCreate<GLPointLight>();

		this->Light->SetAmbient(ambient);
		this->Light->SetDiffuse(diffuse);
		this->Light->SetSpecular(specular);
		this->Light->SetConstant(constant);
		this->Light->SetLinear(linear);
		this->Light->SetQuadratic(quadratic);
	}

	void Initialize() override
	{
		GCube::Initialize();

		this->Scene->AddLight(this->Light);
		this->Transform->SetScale(0.1f, 0.1f, 0.1f);
	}

	~GPointLightObject()
	{
		this->Scene->RemoveLight(this->Light);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "r")
		{
			ToggleDirection(this->RotationDirection, 1);
		}
		else if (key == "R")
		{
			ToggleDirection(this->RotationDirection, -1);
		}
		else if (key == "z")
		{
			ToggleDirection(this->MoveDirection, 1);
		}
		else if (key == "Z")
		{
			ToggleDirection(this->MoveDirection, -1);
		}
		else if (key == "c" || key == "C")
		{
			this->Light->SetAmbient(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
			this->Light->SetDiffuse(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
			this->Light->SetSpecular(Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Light->SetPosition(this->Transform->GetPosition());

		if (this->RotationDirection)
		{
			this->Transform->RotateAround(glm::vec3(0.0f), deltaTime * this->RotationDirection, glm::vec3(0.0f, 1.0f, 0.0f));
		}

		if (this->MoveDirection)
		{
			glm::vec4 front = this->Transform->GetRotation() * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			this->Transform->Translate(glm::vec3(front) * (deltaTime * this->MoveDirection));
		}
	}

	GLSharedPtr<GLPointLight> Light;

	int MoveDirection = 0;
	int RotationDirection = 0;
};

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		this->PerspectiveCamera = GCreate(GPerspectiveCamera, 90.0f);
		this->OrthographicCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);

		this->LightObject = GCreateChild(GPointLightObject, glm::vec3(0.7f), glm::vec3(0.7f), glm::vec3(0.8f), 1.0f, 0.22f, 0.20f);
		this->LightObject->Transform->SetLocalPosition(0.0f, 0.0f, 2.0f);

		this->SolarSystem = GCreate(GSolarSystem);

		this->AddChildren({ this->PerspectiveCamera, this->OrthographicCamera, this->LightObject, this->SolarSystem });

		this->PerspectiveCamera->Initialize();
		this->OrthographicCamera->Initialize();
		this->LightObject->Initialize();
		this->SolarSystem->Initialize();

		this->Scene->AddCamera(this->PerspectiveCamera);
		this->Scene->AddCamera(this->OrthographicCamera);

		this->OrthographicCamera->SetActive(false);

		this->PerspectiveCamera->Transform->Translate(0.0f, 0.5f, 2.0f);
		this->PerspectiveCamera->Transform->Rotate(glm::radians(-20.0f), 0.0f, 0.0f);

		this->OrthographicCamera->Transform->Translate(0.0f, 0.5f, 2.0f);
		this->OrthographicCamera->Transform->Rotate(glm::radians(-20.0f), 0.0f, 0.0f);
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

	GLSharedPtr<GPointLightObject> LightObject;
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
	scene->SetBackgroundColor(GLColor(0.0f, 0.0f, 0.0f));

	auto world = GCreate(GWorld);
	scene->Root->AddChild(world);

	world->Initialize();

	GLLoadScene(scene);

	glutMainLoop();
}