#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/gtc/quaternion.hpp>

#include "../GL/GL.h"

class IsoscelesTriangleMesh : public GLMesh
{
public:
	IsoscelesTriangleMesh(GLfloat w, GLfloat h, const GLColor& color)
		: GLMesh()
	{
		GLPoint v1({ -w / 2.0f, -h / 2.0f, 0.0f }, color);
		GLPoint v2({ w / 2.0f, -h / 2.0f, 0.0f }, color);
		GLPoint v3({ 0.0f, h / 2.0f, 0.0f }, color);

		GLTriangle triangle(v1, v2, v3);
		this->triangles.push_back(triangle);
	}
};

class IsoscelesTriangle : public GLGameObject
{
public:
	IsoscelesTriangle(std::shared_ptr<GLTransform> parent, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
		: GLGameObject(parent), size(w, h)
	{
		GLColor random_color;
		random_color.Rand3f();

		this->mesh_renderer->mesh = std::make_shared<IsoscelesTriangleMesh>(w, h, random_color);

		this->transform->Translate(x, y, 0.0f);
		this->transform->Update();

		this->speed = Rand3v(-0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f);
	}

	glm::vec3 GetCollision()
	{
		glm::vec3 collision_vector(0.0f, 0.0f, 0.0f);

		glm::vec3 world_position = this->transform->GetWorldPosition();

		for (auto& triangle : this->mesh_renderer->mesh->triangles)
		{
			glm::vec3 positions[3] = 
			{
				triangle.v1.position + world_position,
				triangle.v2.position + world_position,
				triangle.v3.position + world_position
			};

			for (auto& position : positions)
			{
				if (position.x < -1.0f)
				{
					collision_vector.x = -1.0f;
				}
				else if (position.x > 1.0f)
				{
					collision_vector.x = 1.0f;
				}

				if (position.y < -1.0f)
				{
					collision_vector.y = -1.0f;
				}
				else if (position.y > 1.0f)
				{
					collision_vector.y = 1.0f;
				}
			}
		}

		return collision_vector;
	}

	GLvoid Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->transform->Translate(this->speed * deltaTime);

		glm::vec3 collision_vector = this->GetCollision();

		if (collision_vector.x < 0.0f && this->speed.x < 0.0f)
		{
			this->transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(-90.0f)));
			this->speed.x = -this->speed.x;
		}

		if (collision_vector.x > 0.0f && this->speed.x > 0.0f)
		{
			this->transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));
			this->speed.x = -this->speed.x;
		}

		if (collision_vector.y < 0.0f && this->speed.y < 0.0f)
		{
			this->transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(0.0f)));
			this->speed.y = -this->speed.y;
		}

		if(collision_vector.y > 0.0f && this->speed.y > 0.0f)
		{
			this->transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(180.0f)));
			this->speed.y = -this->speed.y;
		}
	}

	glm::vec2 size;
	glm::vec3 speed;
};

class TriangleManager : public GLGameObject
{
public:
	TriangleManager(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		glm::vec2 triangle_positions[4] =
		{
			glm::vec2(0.5f, 0.5f),
			glm::vec2(-0.5f, 0.5f),
			glm::vec2(0.5f, -0.5f),
			glm::vec2(-0.5f, -0.5f)
		};

		for (auto i = 0; i < 4; ++i)
		{
			this->children.push_back(std::make_shared<IsoscelesTriangle>(
				this->transform, triangle_positions[i].x, triangle_positions[i].y, 0.15f, 0.2f));
		}
	}

	GLvoid Update(GLfloat delta_time)
	{
		GLGameObject::Update(delta_time);
	}


	GLvoid OnMouseDown(int button, int x, int y)
	{
		if (button == 0)
		{
			glm::vec2 mousePositionWorld = ScreenToWorldPoint(GLMain::GetInstance()->window->Size(), glm::tvec2<int>(x, y));
			auto triangle = std::make_shared<IsoscelesTriangle>(
				this->transform, mousePositionWorld.x, mousePositionWorld.y, 0.15f * size_multiplier, 0.2f * size_multiplier);

			if (this->children.size() == 4)
			{
				this->children.erase(this->children.begin());
			}

			this->children.push_back(triangle);

			this->size_multiplier += this->size_multiplier_direction;

			if (this->size_multiplier > 1.5f || this->size_multiplier < 0.5f)
			{
				this->size_multiplier_direction = -this->size_multiplier_direction;
			}
		}
	}

	GLvoid OnKeyDown(unsigned char key, int x, int y) override
	{
		switch (key)
		{
		case 'a':
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
			break;
		case 'b':
			glPolygonMode(GL_FRONT, GL_LINE);
			glPolygonMode(GL_BACK, GL_LINE);
			break;
		}
	}
private:
	GLfloat size_multiplier = 1.0f;
	GLfloat size_multiplier_direction = 0.2f;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training6");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to Initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	GLMain::SetInstance(std::make_shared<GLMain>(window));

	GLLoadScene(std::make_shared<GLScene>("Training6"));

	auto triangle_manager = std::make_shared<TriangleManager>(GLCurrentScene()->root->transform);
	GLCurrentScene()->root->children.push_back(triangle_manager);

	glutMainLoop();
}