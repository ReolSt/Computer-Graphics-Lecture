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

class OutlineRectangleMesh : public GLMesh
{
public:
	OutlineRectangleMesh(GLfloat w, GLfloat h, const GLColor& color)
	{
		GLPoint v1({ -w / 2.0f, h / 2.0f, 0.0f }, color);
		GLPoint v2({ w / 2.0f, h / 2.0f, 0.0f }, color);
		GLPoint v3({ -w / 2.0f, -h / 2.0f ,0.0f }, color);
		GLPoint v4({ w / 2.0f, -h / 2.0f, 0.0f }, color);

		this->lines.push_back(GLLine(v1, v2));
		this->lines.push_back(GLLine(v3, v4));
		this->lines.push_back(GLLine(v1, v3));
		this->lines.push_back(GLLine(v2, v4));
	}
};

class IsoscelesTriangle : public GLGameObject
{
public:
	IsoscelesTriangle(std::shared_ptr<GLTransform> parent, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
		: GLGameObject(parent), size(w, h), speed(0.0f, 0.0f, 0.0f)
	{
		GLColor random_color;
		random_color.Rand3f();

		this->mesh_renderer->mesh = std::make_shared<IsoscelesTriangleMesh>(w, h, random_color);

		this->transform->Translate(x, y, 0.0f);
		this->transform->Update();
	}

	glm::vec2 size;
	glm::vec3 speed;
};

class OuterTriangle : public IsoscelesTriangle
{
public:
	OuterTriangle(std::shared_ptr<GLTransform> parent, GLfloat x, GLfloat y, GLfloat w, GLfloat h)
		: IsoscelesTriangle(parent, x, y, w, h)
	{
		this->speed = Rand3v(-0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f);

		glm::vec3 world_position = this->transform->GetWorldPosition();

		auto& triangles = this->mesh_renderer->mesh->triangles;

		float left = triangles[0].v1.position.x + world_position.x;
		float right = triangles[0].v1.position.x + world_position.x;
		float top = triangles[0].v1.position.y + world_position.y;
		float bottom = triangles[0].v1.position.y + world_position.y;

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
				left = glm::min(left, position.x);
				right = glm::max(right, position.x);
				bottom = glm::min(bottom, position.y);
				top = glm::max(top, position.y);
			}
		}
		std::cout << left << " " << right << std::endl;
		std::cout << top << " " << bottom << std::endl;
	}

	glm::vec3 GetCollision()
	{
		glm::vec3 collision_vector(0.0f, 0.0f, 0.0f);

		glm::vec3 world_position = this->transform->GetWorldPosition();

		auto& triangles = this->mesh_renderer->mesh->triangles;

		float left = triangles[0].v1.position.x + world_position.x;
		float right = triangles[0].v1.position.x + world_position.x;
		float top = triangles[0].v1.position.y + world_position.y;
		float bottom = triangles[0].v1.position.y + world_position.y;

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
				left = glm::min(left, position.x);
				right = glm::max(right, position.x);
				bottom = glm::min(bottom, position.y);
				top = glm::max(top, position.y);
			}		
		}

		if (left < -1.0f)
		{
			collision_vector.x = -1.0f;
		}

		if (right > 1.0f)
		{
			collision_vector.x = 1.0f;
		}

		if (bottom < -1.0f)
		{
			collision_vector.y = -1.0f;
		}

		if (top > 1.0f)
		{
			collision_vector.y = 1.0f;
		}

		if ((bottom < 0.5f && bottom > -0.5f) ||
			(top < 0.5f && bottom > -0.5f))
		{
			if (right > -0.5f && right < 0.0f)
			{
				collision_vector.x = 1.0f;
			}
			else if (left < 0.5f && left > 0.0f)
			{
				collision_vector.x = -1.0f;
			}
		}

		if ((left > -0.5f && left < 0.5f) ||
			(right > -0.5f && right < 0.5f))
		{
			if (top > -0.5f && top < 0.0f)
			{
				collision_vector.y = 1.0f;
			}
			else if (bottom < 0.5f && bottom > 0.0f)
			{
				collision_vector.y = -1.0f;
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

		if (collision_vector.y > 0.0f && this->speed.y > 0.0f)
		{
			this->transform->rotation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(180.0f)));
			this->speed.y = -this->speed.y;
		}
	}

	glm::vec3 speed;
};

class InnerTriangle : public IsoscelesTriangle
{
public:
	InnerTriangle(std::shared_ptr<GLTransform> parent, GLfloat x, GLfloat y, GLfloat w, GLfloat h, float direction)
		: IsoscelesTriangle(parent, x, y, w, h)
	{
		this->speed = glm::vec3(Rand(0.5f, 1.5f), 0.0f, 0.0f);
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

			float min_x = 0.0f;
			float max_x = 0.0f;

			for (auto& position : positions)
			{
				min_x = glm::min(min_x, position.x);
				max_x = glm::max(max_x, position.x);
			}

			if (min_x <= -0.5f)
			{
				collision_vector.x = -1.0f;
			}
			else if (max_x >= 0.5f)
			{
				collision_vector.x = 1.0f;
			}
		}

		return collision_vector;
	}
	GLvoid Update(GLfloat deltaTime) override
	{
		GLGameObject::Update(deltaTime);

		this->transform->Translate(this->speed * this->direction * deltaTime);

		glm::vec3 collision_vector = this->GetCollision();

		if ((collision_vector.x < 0.0f && this->direction < 0.0f) ||
			(collision_vector.x > 0.0f && this->direction > 0.0f))
		{
			this->direction = -this->direction;
		}
	}

	float direction = 1.0f;
};

class OutlineRectangle : public GLGameObject
{
public:
	OutlineRectangle(const std::shared_ptr<GLTransform>& parent, float x, float y, float w, float h)
	{
		GLColor random_color;
		random_color.Rand3f();

		this->mesh_renderer->mesh = std::make_shared<OutlineRectangleMesh>(w, h, random_color);

		this->transform->Translate(x, y, 0.0f);
		this->transform->Update();
	}
};

class TriangleManager : public GLGameObject
{
public:
	TriangleManager(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->children.push_back(std::make_shared<OuterTriangle>(
			this->transform, 0.0f, -0.8f, 0.15f, 0.2f));

		auto upper_triangle = std::make_shared<InnerTriangle>(
			this->transform, 0.0f, 0.4f, 0.2f, 0.2f, 1.0f);
		this->children.push_back(upper_triangle);

		auto lower_triangle = std::make_shared<InnerTriangle>(
			this->transform, 0.0f, -0.4f, 0.2f, 0.2f, -1.0f);
		this->children.push_back(lower_triangle);
	}


	GLvoid OnMouseDown(int button, int x, int y)
	{
		if (button == 0)
		{
			glm::vec2 mousePositionWorld = ScreenToWorldPoint(GLMain::GetInstance()->window->Size(), glm::tvec2<int>(x, y));
			std::shared_ptr<GLGameObject> triangle = nullptr;
			if (mousePositionWorld.x > -0.5f && mousePositionWorld.x < 0.5f &&
				mousePositionWorld.y > -0.5f && mousePositionWorld.y < 0.5f)
			{
				float direction = glm::sign(Rand(-1.0f, 1.0f));
				triangle = std::make_shared<InnerTriangle>(
					this->transform, mousePositionWorld.x, mousePositionWorld.y, 0.15f, 0.2f, direction);
			}
			else
			{
				triangle = std::make_shared<OuterTriangle>(
					this->transform, mousePositionWorld.x, mousePositionWorld.y, 0.15f * size_multiplier, 0.2f * size_multiplier);

				this->size_multiplier += this->size_multiplier_direction;

				if (this->size_multiplier > 1.2f || this->size_multiplier < 0.4f)
				{
					this->size_multiplier_direction = -this->size_multiplier_direction;
				}
			}

			if (this->children.size() == 4)
			{
				this->children.erase(this->children.begin());
			}

			this->children.push_back(triangle);			
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

	float size_multiplier = 1.0f;
	float size_multiplier_direction = 0.1f;
};

class EnvironmentManager : public GLGameObject
{
public:
	EnvironmentManager(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->children.push_back(std::make_shared<TriangleManager>(this->transform));
		this->children.push_back(std::make_shared<OutlineRectangle>(this->transform, 0.0f, 0.0f, 1.0f, 1.0f));
	}

	GLvoid Update(GLfloat delta_time)
	{
		GLGameObject::Update(delta_time);
	}

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

	auto environment_manager = std::make_shared<EnvironmentManager>(GLCurrentScene()->root->transform);
	GLCurrentScene()->root->children.push_back(environment_manager);

	glutMainLoop();
}