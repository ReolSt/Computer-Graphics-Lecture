#include <iostream>
#include <memory>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "../GL/GL.h"

class PolyhedronObject : public GLGameObject
{
public:
	PolyhedronObject(const std::shared_ptr<GLTransform>& parent,
		             const std::shared_ptr<GLMesh>& mesh)
		: GLGameObject(parent)
	{
		this->AttachMesh(mesh);

		this->transform->Rotate(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);
		this->transform->SetScale(0.5f, 0.5f, 0.5f);
	}

	void AttachMesh(const std::shared_ptr<GLMesh>& mesh)
	{
		this->mesh_renderer->mesh = mesh;

		for (auto& vertex : mesh->vertices)
		{
			GLColor color;
			color.Rand3f();
			vertex.color = color;
		}
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->rotation_direction.x)
		{
			this->transform->Rotate(delta_time * this->rotation_direction.x, 0.0f, 0.0f);
		}

		if (this->rotation_direction.y)
		{
			this->transform->Rotate(0.0f, delta_time * this->rotation_direction.y, 0.0f);
		}

		if (this->rotation_direction.z)
		{
			this->transform->Rotate(0.0f, 0.0f, delta_time * this->rotation_direction.z);
		}
	}

	glm::tvec3<int> rotation_direction = glm::tvec3<int>(0, 0, 0);
};

class AxisObject : public GLGameObject
{
public:
	AxisObject(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		auto mesh = std::make_shared<GLAxis3DMesh>();
		this->mesh_renderer->mesh = mesh;

		this->transform->Rotate(glm::radians(0.0f), glm::radians(30.0f), glm::radians(0.0f));

		for (auto& vertex : mesh->vertices)
		{
			vertex.color = GLColor(0.0f, 0.0f, 0.0f);
		}

		this->transform->SetScale(20.0f, 20.0f, 20.0f);
	}
};

class OrbitRotator : public GLGameObject
{
public:
	OrbitRotator(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->objectA = std::make_shared<PolyhedronObject>(this->transform, std::make_shared<GLCubeMesh>());
		this->objectB = std::make_shared<PolyhedronObject>(this->transform, std::make_shared<GLConeMesh>());

		this->axis = std::make_shared<AxisObject>(this->transform);

		this->children.insert(this->children.end(), { objectA, objectB, axis });
		this->objectA->transform->Translate(-0.5f, 0.0f, 0.0f);
		this->objectB->transform->Translate(0.5f, 0.0f, 0.0f);

		this->state = 0;

		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->orbit_direction)
		{
			this->transform->Rotate(0.0f, this->orbit_direction * delta_time, 0.0f);
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		GLGameObject::OnKeyDown(key, x, y);

		std::cout << key << std::endl;

		if (key == "x")
		{
			this->objectA->rotation_direction.x = this->objectA->rotation_direction.x == 1 ? 0 : 1;
		}
		else if (key == "X")
		{
			this->objectA->rotation_direction.x = this->objectA->rotation_direction.x == -1 ? 0 : -1;
		}
		else if (key == "y")
		{
			this->objectA->rotation_direction.y = this->objectA->rotation_direction.y == 1 ? 0 : 1;
		}
		else if (key == "Y")
		{
			this->objectA->rotation_direction.y = this->objectA->rotation_direction.y == -1 ? 0 : -1;
		}
		else if (key == "a")
		{
			this->objectB->rotation_direction.x = this->objectB->rotation_direction.x == 1 ? 0: 1;
		}
		else if (key == "A")
		{
			this->objectB->rotation_direction.x = this->objectB->rotation_direction.x == -1 ? 0 : -1;
		}
		else if (key == "b")
		{
			this->objectB->rotation_direction.y = this->objectB->rotation_direction.y == 1 ? 0 : 1;
		}
		else if (key == "B")
		{
			this->objectB->rotation_direction.y = this->objectB->rotation_direction.y == -1 ? 0 : -1;
		}
		else if (key == "r")
		{
			this->orbit_direction = this->orbit_direction == 1 ? 0 : 1;
		}
		else if (key == "R")
		{
			this->orbit_direction = this->orbit_direction == -1 ? 0 : -1;
		}
		else if (key == "c")
		{
			if (this->state == 0)
			{
				this->objectA->AttachMesh(std::make_shared<GLCylinderMesh>());
				this->objectB->AttachMesh(std::make_shared<GLConeMesh>(5));
			}
			else if (this->state == 1)
			{
				this->objectA->AttachMesh(std::make_shared<GLUVSphereMesh>());
				this->objectB->AttachMesh(std::make_shared<GLCubeMesh>());
			}
			else if (this->state == 2)
			{
				this->objectA->AttachMesh(std::make_shared<GLCubeMesh>());
				this->objectB->AttachMesh(std::make_shared<GLConeMesh>());
			}

			this->state = (this->state + 1) % 3;
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
			this->objectA->AttachMesh(std::make_shared<GLCubeMesh>());
			this->objectB->AttachMesh(std::make_shared<GLConeMesh>());

			this->state = 0;

			this->transform->SetEulerAngles(0.0f, 0.0f, 0.0f);

			this->objectA->transform->SetEulerAngles(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);
			this->objectB->transform->SetEulerAngles(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);

			this->objectA->rotation_direction = glm::tvec3<int>(0, 0, 0);
			this->objectB->rotation_direction = glm::tvec3<int>(0, 0, 0);
			this->orbit_direction = 0;
		}
	}

	std::shared_ptr<PolyhedronObject> objectA;
	std::shared_ptr<PolyhedronObject> objectB;

	std::shared_ptr<AxisObject> axis;
	int state = 0;

	int orbit_direction = 0;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 800, "Training15");
	
	InitializeGLEW();

	GLMain::GetInstance()->window = window;

	auto scene = std::make_shared<GLScene>("Training15");

	GLLoadScene(scene);

	scene->root->children.push_back(std::make_shared<OrbitRotator>(scene->root->transform));
	auto camera = std::make_shared<GLCamera>(scene->root->transform, 800, 800, 90.0f);
	camera->transform->Translate(0.0f, 1.0f, 2.0f);
	camera->transform->Rotate(glm::radians(-30.0f), 0.0f, 0.0f);

	scene->active_camera = camera;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	glutMainLoop();
}