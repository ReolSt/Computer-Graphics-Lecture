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

class TriangleMesh : public GLMesh
{
public:
	TriangleMesh(GLfloat h, const GLColor& color) 
		: GLMesh()
	{
		GLPoint v1({ -h / 2.0f, -h / 2.0f, 0.0f }, color);
		GLPoint v2({ h / 2.0f, -h / 2.0f, 0.0f }, color);
		GLPoint v3({ 0.0f, h / 2.0f, 0.0f }, color);

		GLTriangle triangle(v1, v2, v3);
		this->triangles.push_back(triangle);
	}
};

class Triangle : public GLGameObject
{
public:
	Triangle(std::shared_ptr<GLTransform>& parent, glm::vec3 position, GLfloat h, const GLColor& color)
		: GLGameObject(parent), height(h)
	{
		auto mesh = std::make_shared<TriangleMesh>(h, color);
		this->mesh_renderer->mesh = mesh;

		this->transform->position = position;
		this->transform->Update();
	}

	float height;
};

class TrianglePathway : public GLGameObject
{
public:
	TrianglePathway(std::shared_ptr<GLTransform>& parent) 
		: GLGameObject(parent)
	{
		for (int i = 9; i >= -9; i -= 2)
		{
			for (int j = -0.9 * this->pathway_precise; j <= 0.9 * this->pathway_precise; ++j)
			{
				glm::vec3 path(j / this->pathway_precise * ((i - 1) % 4 ? -1 : 1), i / 10.0f, 0.0f);
				this->pathway.push_back(path);
			}

			if (i == -9)
			{
				break;
			}

			for (int j = 0; j < 0.2 * this->pathway_precise; ++j)
			{
				glm::vec3 path(0.9f * ((i - 1) % 4 ? -1 : 1), i / 10.0f - j / this->pathway_precise, 0.0f);
				this->pathway.push_back(path);
			}
		}

		this->triangle_color.Rand3f();

		auto triangle_object = std::make_shared<Triangle>(
			this->transform, this->pathway[0], 0.18f, this->triangle_color);
		this->children.push_back(triangle_object);
		
	}

	void Update(float delta_time)
	{
		GLGameObject::Update(delta_time);

		if (!this->is_moving)
		{
			return;
		}

		for (int i = 0; i < this->children.size(); ++i)
		{
			auto triangle = std::dynamic_pointer_cast<Triangle>(this->children[i]);

			int current_index =
				pathway_index - this->pathway_direction * i * this->pathway_step + this->pathway_offset * ((i + 1) / 2);
			if (current_index < 0 || current_index >= this->pathway.size())
			{
				triangle->visible = false;
			}
			else
			{
				triangle->visible = true;
				triangle->transform->position = this->pathway[current_index];
			}
		}

		this->pathway_index += this->pathway_direction * this->pathway_speed;
		this->pathway_index = glm::max(0, this->pathway_index);
		this->pathway_index = glm::min(this->pathway_index, (int)this->pathway.size() - 1);
	}

	void OnMouseDown(int button, int x, int y) override
	{
		if (button == 0)
		{
			if (this->children.size() < 6)
			{
				auto new_triangle = std::make_shared<Triangle>(
					this->transform, this->pathway[this->pathway_index], 0.18f, this->triangle_color);
				this->children.push_back(new_triangle);
			}
		}

		if (button == 2)
		{
			if (this->children.size())
			{
				this->children.erase(this->children.end() - 1);
			}
		}
		
		GLGameObject::OnMouseDown(button, x, y);		
	}

	void OnKeyDown(unsigned char key, int x, int y) override
	{
		switch (key)
		{
		case 'm':
			this->is_moving = !this->is_moving;
			break;
		case 'n':
			this->pathway_index -= this->pathway_step * pathway_direction * (this->children.size() - 1);
			this->pathway_direction = -this->pathway_direction;
			break;
		case '+':
		case '=':
			this->pathway_speed += 2;
			break;
		case '-':
			this->pathway_speed = glm::max(0, this->pathway_speed - 2);
			break;
		case 'a':
			this->pathway_offset = 0;
			break;
		case 'b':
			this->pathway_offset = 50;
			break;
		case 'c':
			this->triangle_color.Rand3f();

			for (auto& triangle : this->children)
			{
				auto& mesh = triangle->mesh_renderer->mesh;
				mesh->triangles[0].v1.color = this->triangle_color;
				mesh->triangles[0].v2.color = this->triangle_color;
				mesh->triangles[0].v3.color = this->triangle_color;
			}
			break;
		case 'q':
			glutLeaveMainLoop();
			break;
		}

		GLGameObject::OnKeyDown(key, x, y);
	}
	
	GLColor triangle_color;

	std::vector<glm::vec3> pathway;
	int pathway_index = 0;
	int pathway_step = 220;
	int pathway_offset = 0;
	int pathway_speed = 10;
	int pathway_direction = 1;
	float pathway_precise = 1000;

	bool is_moving = false;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training8");

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

	GLLoadScene(std::make_shared<GLScene>("Training8"));

	auto pathway = std::make_shared<TrianglePathway>(GLCurrentScene()->root->transform);
	GLCurrentScene()->root->children.push_back(pathway);

	glutMainLoop();
}