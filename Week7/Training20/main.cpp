#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "../GL/GL.h"

void ToggleDirection(int& direction, int T)
{
	direction = direction == T ? 0 : T;
}

void OffDirection(int& direction, int T)
{
	direction = direction == T ? 0 : direction;
}

class GCrane : public GLGameObject
{
public:
	GConstructor(GCrane)
		: GSuperClassInitializer(GLGameObject)
	{
		this->LowerBody = GCreate(GLGameObject);
		this->LowerBodyMesh = GCreate(GCube);

		GAddChildTo(this->LowerBody, this->LowerBodyMesh);

		this->UpperBody = GCreate(GLGameObject);
		this->UpperBodyMesh = GCreate(GCube);
		this->UpperBody->AddChild(this->UpperBodyMesh);

		this->LeftArm = GCreate(GLGameObject);
		this->LeftArmAxis = GCreate(GLGameObject);
		this->LeftArmMesh = GCreate(GCube);
		this->LeftArm->AddChild(this->LeftArmAxis);
		this->LeftArmAxis->AddChild(this->LeftArmMesh);

		this->RightArm = GCreate(GLGameObject);
		this->RightArmAxis = GCreate(GLGameObject);
		this->RightArmMesh = GCreate(GCube);
		this->RightArm->AddChild(this->RightArmAxis);
		this->RightArmAxis->AddChild(this->RightArmMesh);

		RandVertexColor3f(this->LowerBodyMesh);
		RandVertexColor3f(this->UpperBodyMesh);
		RandVertexColor3f(this->LeftArmMesh);
		RandVertexColor3f(this->RightArmMesh);

		this->AddChild(this->LowerBody);

		this->LowerBody->AddChild(this->UpperBody);
		this->UpperBody->AddChildren({ this->LeftArm, this->RightArm });

		this->LowerBodyMesh->Transform->SetLocalScale(1.0f, 0.5f, 1.0f);
		this->UpperBodyMesh->Transform->SetLocalScale(0.7f, 0.5f, 0.7f);
		this->LeftArmMesh->Transform->SetLocalScale(0.6f, 0.2f, 0.2f);
		this->RightArmMesh->Transform->SetLocalScale(0.6f, 0.2f, 0.2f);

		this->Reset();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->LowerBody->Transform->Translate(0.0f, 0.0f, this->Directions.z * deltaTime);
		this->UpperBody->Transform->Rotate(0.0f, this->Directions.y * deltaTime, 0.0f);

		if (this->Amounts.x >= glm::radians(90.0f))
		{
			OffDirection(this->Directions.x, 1);
		}
		else if (this->Amounts.x <= glm::radians(-90.0f))
		{
			OffDirection(this->Directions.x, -1);
		}

		this->LeftArmAxis->Transform->Rotate(-this->Directions.x * deltaTime, 0.0f, 0.0f);
		this->RightArmAxis->Transform->Rotate(this->Directions.x * deltaTime, 0.0f, 0.0f);

		this->Amounts += glm::vec3(this->Directions) * deltaTime;
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "b")
		{
			ToggleDirection(this->Directions.z, 1);
		}
		else if (key == "B")
		{
			ToggleDirection(this->Directions.z, -1);
		}
		else if (key == "m")
		{
			ToggleDirection(this->Directions.y, 1);
		}
		else if (key == "M")
		{
			ToggleDirection(this->Directions.y, -1);
		}
		else if (key == "t")
		{
			ToggleDirection(this->Directions.x, 1);
		}
		else if (key == "T")
		{
			ToggleDirection(this->Directions.x, -1);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);
	}

	void Stop()
	{
		this->Directions = glm::tvec3<int>(0);
	}

	void Reset()
	{
		this->LowerBody->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->UpperBody->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->LeftArm->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->RightArm->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->LeftArmAxis->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);
		this->RightArmAxis->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);

		this->LeftArmMesh->Transform->SetEulerAngles(0.0f, 0.0f, glm::radians(90.0f));
		this->RightArmMesh->Transform->SetEulerAngles(0.0f, 0.0f, glm::radians(-90.0f));

		this->LowerBody->Transform->SetPosition(0.0f, 0.25f, 0.0f);
		this->UpperBody->Transform->SetPosition(0.0f, 0.75f, 0.0f);
		this->LeftArm->Transform->SetPosition(-0.15f, 1.0f, 0.0f);
		this->RightArm->Transform->SetPosition(0.15f, 1.0f, 0.0f);

		this->LeftArmMesh->Transform->SetPosition(-0.15f, 1.3f, 0.0f);
		this->RightArmMesh->Transform->SetPosition(0.15f, 1.3f, 0.0f);

		this->Directions = glm::tvec3<int>(0);
		this->Amounts = glm::vec3(0.0f);
	}

	glm::tvec3<int> Directions = glm::tvec3<int>(0);
	glm::vec3 Amounts = glm::vec3(0.0f);

	GLSharedPtr<GLGameObject> LowerBody;
	GLSharedPtr<GLGameObject> UpperBody;
	GLSharedPtr<GLGameObject> LeftArm;
	GLSharedPtr<GLGameObject> RightArm;

	GLSharedPtr<GLGameObject> LowerBodyMesh;
	GLSharedPtr<GLGameObject> UpperBodyMesh;
	GLSharedPtr<GLGameObject> LeftArmMesh;
	GLSharedPtr<GLGameObject> RightArmMesh;

	GLSharedPtr<GLGameObject> LeftArmAxis;
	GLSharedPtr<GLGameObject> RightArmAxis;
};

class GFloor : public GLGameObject
{
public:
	GConstructor(GFloor)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Shape = GCreate(GRectangle);
		this->AddChild(this->Shape);

		this->Shape->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		this->Shape->Transform->SetLocalScale(10.0f, 10.0f, 10.0f);

		RandVertexColor3f(this->Shape);
	}

	GLSharedPtr<GRectangle> Shape;
};

class GCameraController : public GLGameObject
{
public:
	GConstructor(GCameraController)
		: GSuperClassInitializer(GLGameObject)
	{
		this->PerspectiveCamera = GCreate(GPerspectiveCamera, 90.0f);
		this->FrontCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);
		this->TopCamera = GCreate(GOrthographicCamera, -2.0f, 2.0f, -2.0f, 2.0f);

		this->PerspectiveCamera->SetViewportSize(0.5f, 1.0f);

		this->FrontCamera->SetViewportPosition(0.5f, 0.5f);
		this->FrontCamera->SetViewportSize(0.5f, 0.5f);

		this->TopCamera->SetViewportPosition(0.5f, 0.0f);
		this->TopCamera->SetViewportSize(0.5f, 0.5f);

		this->Scene->AddCamera(this->PerspectiveCamera);
		this->Scene->AddCamera(this->FrontCamera);
		this->Scene->AddCamera(this->TopCamera);

		this->AddChildren({ this->PerspectiveCamera });
		this->Scene->Root->AddChildren({ this->FrontCamera, this->TopCamera });

		this->Reset();
	}

	void Update(float deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->Transform->RotateAround(
			glm::vec3(0.0f, 0.0f, 0.0f), deltaTime * this->RotatingAroundCenter, glm::vec3(0.0f, 1.0f, 0.0f));
		this->FrontCamera->Transform->RotateAround(
			glm::vec3(0.0f, 0.0f, 0.0f), deltaTime * this->RotatingAroundCenter, glm::vec3(0.0f, 1.0f, 0.0f));

		this->Transform->Rotate(deltaTime * this->Rotating, glm::vec3(0.0f, 1.0f, 0.0f));
		this->TopCamera->Transform->Rotate(deltaTime * this->Rotating, glm::vec3(0.0f, 0.0f, 1.0f));

		this->Transform->Translate(glm::vec3(this->Directions) * deltaTime);
		this->FrontCamera->Transform->Translate(glm::vec3(this->Directions) * deltaTime);
		this->TopCamera->Transform->Translate(glm::vec3(this->Directions) * deltaTime);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "z")
		{
			this->Directions.z = 1;
		}
		else if (key == "Z")
		{
			this->Directions.z = -1;
		}
		else if (key == "x")
		{
			this->Directions.x = 1;
		}
		else if (key == "X")
		{
			this->Directions.x = -1;
		}
		else if (key == "y")
		{
			this->Rotating = 1;
		}
		else if (key == "Y")
		{
			this->Rotating = -1;
		}
		else if (key == "r")
		{
			this->RotatingAroundCenter = 1;
		}
		else if (key == "R")
		{
			this->RotatingAroundCenter = -1;
		}
		else if (key == "a")
		{
			this->RotatingAroundCenter = 1;
		}
		else if (key == "A")
		{
			this->RotatingAroundCenter = 0;
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyUp(key, x, y);

		if (key == "z")
		{
			OffDirection(this->Directions.z, 1);
		}
		else if (key == "Z")
		{
			OffDirection(this->Directions.z, -1);
		}
		else if (key == "x")
		{
			OffDirection(this->Directions.x, 1);
		}
		else if (key == "X")
		{
			OffDirection(this->Directions.x, -1);
		}
		else if (key == "y")
		{
			OffDirection(this->Rotating, 1);
		}
		else if (key == "Y")
		{
			OffDirection(this->Rotating, -1);
		}
		else if (key == "r")
		{
			OffDirection(this->RotatingAroundCenter, 1);
		}
		else if (key == "R")
		{
			OffDirection(this->RotatingAroundCenter, -1);
		}
	}

	void Stop()
	{
		this->Rotating = 0;
		this->RotatingAroundCenter = 0;
		this->Directions = glm::tvec3<int>(0);
	}

	void Reset()
	{
		this->Transform->SetPosition(0.0f, 2.0f, 2.5f);
		this->PerspectiveCamera->Transform->SetEulerAngles(glm::radians(-30.0f), 0.0f, 0.0f);

		this->FrontCamera->Transform->SetPosition(0.0f, 0.0f, 2.0f);
		this->FrontCamera->Transform->SetEulerAngles(0.0f, 0.0f, 0.0f);

		this->TopCamera->Transform->SetPosition(0.0f, 2.0f, 0.0f);
		this->TopCamera->Transform->SetEulerAngles(glm::radians(-90.0f), 0.0f, 0.0f);
	}

	int RotatingAroundCenter = 0;
	int Rotating = 0;

	glm::tvec3<int> Directions = glm::tvec3<int>(0);

	GLSharedPtr<GPerspectiveCamera> PerspectiveCamera;
	GLSharedPtr<GOrthographicCamera> FrontCamera;
	GLSharedPtr<GOrthographicCamera> TopCamera;
};

class GWorld : public GLGameObject
{
public:
	GConstructor(GWorld)
		: GSuperClassInitializer(GLGameObject)
	{
		this->CameraController = GCreateChild(GCameraController);
		this->Crane = GCreate(GCrane);
		this->Floor = GCreate(GFloor);

		this->AddChildren({ this->CameraController, this->Crane, this->Floor });
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "s" || key == "S")
		{
			this->CameraController->Stop();
			this->Crane->Stop();
		}
		else if (key == "c" || key == "C")
		{
			this->CameraController->Stop();
			this->Crane->Stop();

			this->CameraController->Reset();
			this->Crane->Reset();
		}
		else if (key == "q" || key == "Q")
		{
			GLMain::GetInstance()->Exit();
		}
	}

	GLSharedPtr<GCameraController> CameraController;
	GLSharedPtr<GCrane> Crane;
	GLSharedPtr<GFloor> Floor;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLSetWindow(GLCreate<GLWindow>(0, 0, 800, 800, "Training20"));

	InitializeGLEW();

	glEnable(GL_DEPTH_TEST);

	auto scene = GLCreate<GLScene>("Training20");
	GCreateAndAddChildFor(scene->Root, GWorld);

	GLLoadScene(scene);

	glutMainLoop();
}