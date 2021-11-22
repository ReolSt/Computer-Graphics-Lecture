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

template <typename ShapeType>
class TShapeWithAxis : public GLGameObject
{
public:
	GConstructor(TShapeWithAxis)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Shape = GCreateChild(ShapeType);
		GAddChild(this->Shape);

		this->Shape->MeshRenderer->GetMaterial()->SetVector("diffuse", glm::vec3(0.2f, 0.5f, 0.4f));
		this->Shape->MeshRenderer->GetMaterial()->SetFloat("shininess", 1.0f);
	}

	GLSharedPtr<ShapeType> Shape;
};

using GTriangleWithAxis = TShapeWithAxis<GTriangle>;
using GRectangleWithAxis = TShapeWithAxis<GRectangle>;

class GDeformableCube : public GLGameObject
{
public:
	GConstructor(GDeformableCube)
		: GSuperClassInitializer(GLGameObject)
	{
		this->Top = GCreateChild(GRectangleWithAxis);
		this->Bottom = GCreateChild(GRectangleWithAxis);
		this->Left = GCreateChild(GRectangleWithAxis);
		this->Right = GCreateChild(GRectangleWithAxis);
		this->Back = GCreateChild(GRectangleWithAxis);
		this->Front = GCreateChild(GRectangleWithAxis);

		this->Top->Transform->Translate(0.0f, 0.5f, 0.0f);
		this->Top->Transform->Rotate(glm::radians(-90.0f), 0.0f, 0.0f);

		this->Bottom->Transform->Translate(0.0f, -0.5f, 0.0f);
		this->Bottom->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->Left->Transform->Translate(-0.5f, 0.0f, 0.0f);
		this->Left->Transform->Rotate(0.0f, glm::radians(-90.0f), 0.0f);

		this->Right->Transform->Translate(0.5f, 0.0f, 0.0f);
		this->Right->Transform->Rotate(0.0f, glm::radians(90.0f), 0.0f);

		this->Back->Transform->Translate(0.0f, -0.5f, -0.5f);
		this->Back->Shape->Transform->Translate(0.0f, 0.5f, 0.0f);
		this->Back->Shape->Transform->Rotate(0.0f, glm::radians(180.0f), 0.0f);

		this->Front->Transform->Translate(0.0f, -0.5f, 0.5f);
		this->Front->Shape->Transform->Translate(0.0f, 0.5f, 0.0f);

		this->AddChildren({ this->Top, this->Bottom, this->Left, this->Right, this->Back, this->Front });
	}

	void Update(GLfloat delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->TopRotationDirection)
		{
			this->Top->Transform->Rotate(delta_time * this->TopRotationDirection, 0.0f, 0.0f);
		}

		if (this->FrontRotationDirection)
		{
			this->Front->Transform->Rotate(delta_time * this->FrontRotationDirection, 0.0f, 0.0f);
			this->FrontRotationAmount += delta_time * this->FrontRotationDirection;

			if (this->FrontRotationAmount > glm::radians(90.0f))
			{
				this->FrontRotationDirection = 0;
				this->FrontRotationAmount = glm::radians(90.0f);

				this->Front->Transform->SetLocalEulerAngles(glm::radians(90.0f), 0.0f, 0.0f);
			}

			if(this->FrontRotationAmount < 0.0f)
			{
				this->FrontRotationDirection = 0;
				this->FrontRotationAmount = 0.0f;

				this->Front->Transform->SetLocalEulerAngles(0.0f, 0.0f, 0.0f);
			}
		}

		if (this->SideSlideDirection)
		{
			this->Left->Transform->Translate(0.0f, delta_time * this->SideSlideDirection, 0.0f);
			this->Right->Transform->Translate(0.0f, delta_time * this->SideSlideDirection, 0.0f);

			this->SideSlideAmount += delta_time * this->SideSlideDirection;

			if (this->SideSlideAmount < 0.0f)
			{
				this->SideSlideDirection = 0;
				this->SideSlideAmount = 0.0f;

				this->Left->Transform->LocalPosition.y = 0.0f;
				this->Right->Transform->LocalPosition.y = 0.0f;
			}

			if (this->SideSlideAmount > 1.0f)
			{
				this->SideSlideDirection = 0;
				this->SideSlideAmount = 1.0f;

				this->Left->Transform->LocalPosition.y = 1.0f;
				this->Right->Transform->LocalPosition.y = 1.0f;
			}
		}
	}

	int TopRotationDirection = 0;

	int FrontRotationDirection = 0;
	float FrontRotationAmount = 0.0f;

	int SideSlideDirection = 0;
	float SideSlideAmount = 0.0f;

	GLSharedPtr<GRectangleWithAxis> Left;
	GLSharedPtr<GRectangleWithAxis> Right;
	GLSharedPtr<GRectangleWithAxis> Bottom;
	GLSharedPtr<GRectangleWithAxis> Top;
	GLSharedPtr<GRectangleWithAxis> Back;
	GLSharedPtr<GRectangleWithAxis> Front;
};

class GDeformablePyramid : public GCone
{
public:
	GConstructor(GDeformablePyramid)
		: GSuperClassInitializer(GCone)
	{

	    this->Floor = GCreateChild(GRectangleWithAxis);
		this->Left = GCreateChild(GTriangleWithAxis);
		this->Right = GCreateChild(GTriangleWithAxis);
		this->Back = GCreateChild(GTriangleWithAxis);
		this->Front = GCreateChild(GTriangleWithAxis);

		this->Floor->Transform->LocalPosition.y -= 0.5f;
		this->Floor->Transform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);

		this->Left->Transform->Translate(-0.5f, -0.5f, 0.0f);
		this->Left->Transform->Rotate(glm::radians(-30.0f), glm::radians(-90.0f), 0.0f);
		this->Left->Shape->Transform->LocalPosition.y += 0.5f;

		this->Right->Transform->Translate(0.5f, -0.5f, 0.0f);
		this->Right->Transform->Rotate(glm::radians(-30.0f), glm::radians(90.0f), 0.0f);
		this->Right->Shape->Transform->LocalPosition.y += 0.5f;

		this->Back->Transform->Translate(0.0f, -0.5f, -0.5f);
		this->Back->Shape->Transform->LocalPosition.y += 0.5f;
		this->Back->Transform->Rotate(glm::radians(30.0f), 0.0f, 0.0f);

		this->Front->Transform->Translate(0.0f, -0.5f, 0.5f);
		this->Front->Shape->Transform->LocalPosition.y += 0.5f;
		this->Front->Transform->Rotate(glm::radians(-30.0f), 180.0f, 0.0f);

		this->MeshRenderer->GetMaterial()->SetVector("diffuse", glm::vec3(0.2f, 0.5f, 0.4f));
		this->MeshRenderer->GetMaterial()->SetFloat("shininess", 0.5f);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->RotationDirection)
		{
			this->Left->Transform->Rotate(delta_time * this->RotationDirection, 0.0f, 0.0f);
			this->Right->Transform->Rotate(delta_time * this->RotationDirection, 0.0f, 0.0f);
			this->Back->Transform->Rotate(delta_time * -this->RotationDirection, 0.0f, 0.0f);
			this->Front->Transform->Rotate(delta_time * this->RotationDirection, 0.0f, 0.0f);

			this->RotationAmount += delta_time * this->RotationDirection;

			if (this->RotationAmount < 0.0f)
			{
				this->RotationDirection = 0;
				this->RotationAmount = 0.0f;

				this->Left->Transform->SetLocalEulerAngles(glm::radians(-30.0f), glm::radians(-90.0f), 0.0f);
				this->Right->Transform->SetLocalEulerAngles(glm::radians(-30.0f), glm::radians(90.0f), 0.0f);
				this->Back->Transform->SetLocalEulerAngles(glm::radians(30.0f), 0.0f, 0.0f);
				this->Front->Transform->SetLocalEulerAngles(glm::radians(-30.0f), 0.0f, 0.0f);
			}

			if (this->RotationAmount > glm::radians(120.0f))
			{
				this->RotationDirection = 0;
				this->RotationAmount = glm::radians(120.0f);

				this->Left->Transform->SetLocalEulerAngles(glm::radians(90.0f), glm::radians(-90.0f), 0.0f);
				this->Right->Transform->SetLocalEulerAngles(glm::radians(90.0f), glm::radians(90.0f), 0.0f);
				this->Back->Transform->SetLocalEulerAngles(glm::radians(-90.0f), 0.0f, 0.0f);
				this->Front->Transform->SetLocalEulerAngles(glm::radians(90.0f), 0.0f, 0.0f);
			}
		}
	}

	int RotationDirection = 0;
	float RotationAmount = 0;

	GLSharedPtr<GRectangleWithAxis> Floor;
	GLSharedPtr<GTriangleWithAxis> Left;
	GLSharedPtr<GTriangleWithAxis> Right;
	GLSharedPtr<GTriangleWithAxis> Back;
	GLSharedPtr<GTriangleWithAxis> Front;
};

class GPointLightObject : public GCube
{
public:
	GConstructor(GPointLightObject, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	             float constant, float linear, float quadratic)
		: GSuperClassInitializer(GCube)
	{
		this->Light = GLCreate<GLPointLight>();
		this->Scene->AddLight(this->Light);

		this->Light->SetAmbient(ambient);
		this->Light->SetDiffuse(diffuse);
		this->Light->SetSpecular(specular);
		this->Light->SetConstant(constant);
		this->Light->SetLinear(linear);
		this->Light->SetQuadratic(quadratic);

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

class GDeformAnimationDisplayer : public GLGameObject
{
public:
	GConstructor(GDeformAnimationDisplayer)
		: GSuperClassInitializer(GLGameObject)
	{
		this->PerspectiveCamera = GCreateChildFor(Scene->Root, GPerspectiveCamera, 90.0f);
		this->OrthographicCamera = GCreateChildFor(Scene->Root, GOrthographicCamera,
			-4.0f, 4.0f, -4.0f, 4.0f);

		this->Scene->Root->AddChildren({ this->PerspectiveCamera, this->OrthographicCamera });

		this->Scene->AddCamera(this->PerspectiveCamera);
		this->Scene->AddCamera(this->OrthographicCamera);

		this->OrthographicCamera->SetActive(false);

		this->PerspectiveCamera->Transform->Translate(0.0f, 2.0f, 2.0f);
		this->PerspectiveCamera->Transform->Rotate(glm::radians(-45.0f), 0.0f, 0.0f);

		this->OrthographicCamera->Transform->Translate(0.0f, 2.0f, 2.0f);
		this->OrthographicCamera->Transform->Rotate(glm::radians(-45.0f), 0.0f, 0.0f);

		this->LightObject = GCreateChild(GPointLightObject, glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(0.8f), 1.0f, 0.22f, 0.20f);
		this->LightObject->Transform->SetLocalPosition(0.0f, 0.0f, 1.0f);

		this->AddChild(this->LightObject);

		this->Cube = GCreateChild(GDeformableCube);
		this->Pyramid = GCreateChild(GDeformablePyramid);
		this->Axis = GCreateChild(GAxis3D, GLColor(0.0f, 0.0f, 0.0f));

		this->Cube->Transform->Rotate(0.0f, glm::radians(-30.0f), 0.0f);
		this->Pyramid->Transform->Rotate(0.0f, glm::radians(-30.0f), 0.0f);
		this->Axis->Transform->Rotate(0.0f, glm::radians(-30.0f), 0.0f);

		this->Cube->SetVisible(true);
		this->Pyramid->SetVisible(false);

		this->Axis->Transform->SetLocalScale(10.0f, 10.0f, 10.0f);
		
		this->AddChildren({ this->Cube, this->Pyramid, this->Axis });
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->RotationDirection)
		{
			this->Cube->Transform->Rotate(0.0f, delta_time * this->RotationDirection, 0.0f);
			this->Pyramid->Transform->Rotate(0.0f, delta_time * this->RotationDirection, 0.0f);
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		if (key == "h")
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
		else if (key == "y")
		{
			ToggleDirection(this->RotationDirection, 1);
		}
		else if (key == "Y")
		{
			ToggleDirection(this->RotationDirection, -1);
		}
		else if (key == "t")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->TopRotationDirection, 1);
		}
		else if (key == "T")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->TopRotationDirection, -1);
		}
		else if (key == "f")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->FrontRotationDirection, 1);
		}
		else if (key == "F")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->FrontRotationDirection, -1);
		}
		else if (key == "1")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->SideSlideDirection, 1);
		}
		else if (key == "2")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
			ToggleDirection(this->Cube->SideSlideDirection, -1);
		}
		else if (key == "o")
		{
			this->Cube->SetVisible(false);
			this->Pyramid->SetVisible(true);
			ToggleDirection(this->Pyramid->RotationDirection, 1);
		}
		else if (key == "O")
		{
			this->Cube->SetVisible(false);
			this->Pyramid->SetVisible(true);
			ToggleDirection(this->Pyramid->RotationDirection, -1);
		}
		else if (key == "p")
		{
			this->PerspectiveCamera->SetActive(true);
			this->OrthographicCamera->SetActive(false);
		}
		else if (key == "P")
		{
			this->PerspectiveCamera->SetActive(false);
			this->OrthographicCamera->SetActive(true);
		}
		else if (key == "n")
		{
			this->Cube->SetVisible(true);
			this->Pyramid->SetVisible(false);
		}
		else if (key == "N")
		{
			this->Cube->SetVisible(false);
			this->Pyramid->SetVisible(true);
		}
		else if (key == "m")
		{
			this->LightObject->Light->SetActive(true);
		}
		else if (key == "M")
		{
			this->LightObject->Light->SetActive(false);
		}
	}

	GLSharedPtr<GPerspectiveCamera> PerspectiveCamera;
	GLSharedPtr<GOrthographicCamera> OrthographicCamera;

	GLSharedPtr<GPointLightObject> LightObject;

	GLSharedPtr<GDeformableCube> Cube;
	GLSharedPtr<GDeformablePyramid> Pyramid;
	GLSharedPtr<GAxis3D> Axis;

	int RotationDirection = 0;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	GLMain::GetInstance()->Window = GLCreate<GLWindow>(0, 0, 800, 800, "Training17");

	InitializeGLEW();

	auto scene = GLCreate<GLScene>("Training17");
	GLLoadScene(scene);

	GCreateAndAddChildFor(scene->Root, GDeformAnimationDisplayer);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glutMainLoop();
}