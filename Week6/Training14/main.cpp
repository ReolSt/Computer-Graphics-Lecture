#include <iostream>
#include <memory>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <gl/glm/glm.hpp>

#include "../GL/GL.h"

class TransformableObject : public GLGameObject
{
public:
	TransformableObject(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent), t_direction(0, 0, 0), r_direction(0, 0, 0)
	{
		this->cube_mesh = std::make_shared<GLCubeMesh>();
		this->pyramid_mesh = std::make_shared<GLConeMesh>(4);

		GLColor colors[8] = {
			GLColor(1.0f, 0.0f, 0.0f),
			GLColor(0.0f, 1.0f, 0.0f),
			GLColor(0.0f, 0.0f, 1.0f),
			GLColor(1.0f, 1.0f, 0.0f),
			GLColor(0.0f, 1.0f, 1.0f),
			GLColor(1.0f, 0.0f, 1.0f),
			GLColor(0.5f, 0.5f, 1.0f),
			GLColor(1.0f, 0.5f, 0.5f)
		};

		for (auto i = 0; i < cube_mesh->vertices.size(); ++i)
		{
			cube_mesh->vertices[i].color = colors[i];
		}

		for (auto i = 0; i < pyramid_mesh->vertices.size(); ++i)
		{
			pyramid_mesh->vertices[i].color = colors[i];
		}

		this->mesh_renderer->mesh = cube_mesh;

		this->transform->Rotate(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);
	}

	void Update(GLfloat delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->t_direction.x)
		{
			this->transform->Translate(delta_time * this->t_direction.x, 0.0f, 0.0f);
		}

		if (this->t_direction.y)
		{
			this->transform->Translate(0.0f, delta_time * this->t_direction.y, 0.0f);
		}

		if (this->t_direction.z)
		{
			this->transform->Translate(0.0f, 0.0f, delta_time * this->t_direction.z);
		}

		if (this->r_direction.x)
		{
			this->transform->Rotate(delta_time * this->r_direction.x, 0.0f, 0.0f);
		}

		if (this->r_direction.y)
		{
			this->transform->Rotate(0.0f, delta_time * this->r_direction.y, 0.0f);
		}

		if (this->r_direction.z)
		{
			this->transform->Rotate(0.0f, 0.0f, delta_time * this->r_direction.z);
		}
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		if (key == "c")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
		}
		else if (key == "p")
		{
			this->mesh_renderer->mesh = this->pyramid_mesh;
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
			this->t_direction.x = this->t_direction.x = -1;
		}
		else if (key == "Right")
		{
			this->t_direction.x = this->t_direction.x = 1;
		}
		else if (key == "Down")
		{
			this->t_direction.y = this->t_direction.y = -1;
		}
		else if (key == "Up")
		{
			this->t_direction.y = this->t_direction.y = 1;
		}
		else if (key == "x")
		{
			this->r_direction.x = this->r_direction.x != 1 ? 1 : 0;
		}
		else if (key == "X")
		{
			this->r_direction.x = this->r_direction.x != -1 ? -1 : 0;
		}
		else if (key == "y")
		{
			this->r_direction.y = this->r_direction.y != 1 ? 1 : 0;
		}
		else if (key == "Y")
		{
			this->r_direction.y = this->r_direction.y != -1 ? -1 : 0;
		}
		else if (key == "z")
		{
			this->r_direction.z = this->r_direction.z != 1 ? 1 : 0;
		}
		else if (key == "Z")
		{
			this->r_direction.z = this->r_direction.z != -1 ? -1 : 0;
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
			this->transform->local_position = glm::vec3(0.0f, 0.0f, 0.0f);
			this->transform->SetEulerAngles(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);

			this->t_direction = glm::tvec3<int>(0, 0, 0);
			this->r_direction = glm::tvec3<int>(0, 0, 0);
		}
	}

	void OnKeyUp(const std::string& key, int x, int y) override
	{
		if (key == "Up")
		{
			this->t_direction.y = 0;
		}
		else if (key == "Down")
		{
			this->t_direction.y = 0;
		}
		else if (key == "Left")
		{
			this->t_direction.x = 0;
		}
		else if (key == "Right")
		{
			this->t_direction.x = 0;
		}
	}

	glm::tvec3<int> t_direction;
	glm::tvec3<int> r_direction;

	std::shared_ptr<GLMesh> cube_mesh;
	std::shared_ptr<GLMesh> pyramid_mesh;
};

class AxisObject : public GLGameObject
{
public:
	AxisObject(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		auto axis_mesh = std::make_shared<GLAxis3DMesh>();
		this->mesh_renderer->mesh = axis_mesh;

		for (auto& vertex : axis_mesh->vertices)
		{
			vertex.color = GLColor(0.0f, 0.0f, 0.0f);
		}

		this->transform->SetScale(3.0f, 3.0f, 3.0f);
	}
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 800, "Training14");

	InitializeGLEW();

	GLMain::GetInstance()->window = window;

	auto scene = std::make_shared<GLScene>("Training14");
	auto camera = std::make_shared<GLCamera>(scene->root->transform, 800, 800, 90.0f);
	camera->transform->Translate(0.0f, 0.0f, 1.5f);

	scene->active_camera = camera;

	scene->root->children.push_back(camera);

	GLLoadScene(scene);

	scene->root->children.push_back(std::make_shared<TransformableObject>(scene->root->transform));
	scene->root->children.push_back(std::make_shared<AxisObject>(scene->root->transform));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glutMainLoop();
}