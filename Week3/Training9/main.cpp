#include <iostream>
#include <vector>
#include <memory>
#include <random>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/gtc/quaternion.hpp>

#include "../GL/GL.h"

class DoubleSpiral : public GLGameObject
{
public:
	DoubleSpiral(std::shared_ptr<GLTransform>& parent, float x, float y, float size, int precision, const GLColor& color)
		: GLGameObject(parent)
	{
		this->transform->Translate(x, y, 0.0f);
		this->transform->Update();

		this->size = size;

		this->precision = precision;
		this->time_step = -this->precision;

		this->color = color;
	}

	void Next(float time_step, float precision)
	{
		int sign = glm::sign(time_step);

		float radian = glm::pi<float>() * 4.0f * (precision - glm::abs(time_step)) * sign / precision;
		float spiral_size = this->size * (precision - glm::abs(time_step)) * sign / (float)precision;

		GLPoint p;
		p.color = this->color;

		if (time_step < 0)
		{
			p.position = glm::vec3(-glm::cos(radian), -glm::sin(radian), 0.0f) * spiral_size;
		}
		else
		{
			p.position = glm::vec3(-glm::cos(radian), glm::sin(radian), 0.0f) * spiral_size;
		}

		p.position.x += glm::sign(time_step) * this->size;

		this->mesh_renderer->mesh->points.push_back(p);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		if (this->time_step <= precision)
		{
			int offset = glm::max(1, (int)glm::sqrt(this->precision));
			while (offset)
			{
				this->Next(this->time_step, this->precision);
				this->time_step += 1;
				--offset;
			}
		}
	}

	int time_step;
	int precision;

	float size;

	GLColor color;
};

class DoubleSpiralCreator : public GLGameObject
{
public:
	DoubleSpiralCreator(std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLCurrentScene()->background = GLColor(0.0f, 0.0f, 0.0f);

		glPointSize(3.0f);
	}

	void OnMouseDown(int button, int x, int y) override
	{
		if (button == 0)
		{
			auto mouse_world_position = ScreenToWorldPoint(GLMain::GetInstance()->window->Size(), x, y);

			auto& scene = GLCurrentScene();
			scene->background.Rand3f();

			GLColor inverted_color(1.0f - scene->background.r, 1.0f - scene->background.g, 1.0f - scene->background.b);

			auto double_spiral = std::make_shared<DoubleSpiral>(
				this->transform, mouse_world_position.x, mouse_world_position.y, 0.2f, this->precision, inverted_color);
			this->children.clear();
			this->children.push_back(double_spiral);
		}
	}

	void OnMouseWheel(int wheel, int direction, int x, int y) override
	{
		if (direction > 0)
		{
			this->precision *= 1.1;
		}
		else if (direction < 0)
		{
			this->precision *= 0.9;
			this->precision = glm::max(50, this->precision);
		}

		std::cout << "Current Precision: " << this->precision << std::endl;
	}

	int precision = 100;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training9");

	glewExperimental = true;
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

	GLLoadScene(std::make_shared<GLScene>("Training9"));

	auto& scene = GLCurrentScene();
	scene->root->children.push_back(
		std::make_shared<DoubleSpiralCreator>(scene->root->transform));

	glutMainLoop();
}