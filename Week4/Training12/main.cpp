#include <iostream>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GL.h"

class RectangleObject : public GLGameObject
{
public:
	RectangleObject(const std::shared_ptr<GLTransform>& parent,
		const glm::vec3& position,
		const glm::vec3& size,
		const GLColor& color)
		: GLGameObject(parent)
	{
		GLPoint left_top({ -0.5f, 0.5f, 0.0f }, color);
		GLPoint right_top({ 0.5f, 0.5f, 0.0f }, color);
		GLPoint left_bottom({ -0.5f, -0.5f, 0.0f }, color);
		GLPoint right_bottom({ 0.5f, -0.5f, 0.0f }, color);

		this->transform->position = position;
		this->transform->scale = size;

		auto& mesh = this->mesh_renderer->mesh;
		mesh->triangles.push_back(GLTriangle(left_top, right_top, left_bottom));
		mesh->triangles.push_back(GLTriangle(left_bottom, right_top, right_bottom));
	}
};

class RectangleCreator : public GLGameObject
{
public:
	RectangleCreator(std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->eraser = std::make_shared<RectangleObject>(
			this->transform, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.0f), GLColor(0.0f, 0.0f, 0.0f));
		this->children.push_back(eraser);

		this->eraser->visible = false;

		for (auto i = 0; i < 100; ++i)
		{
			glm::vec3 position = Rand3v(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f);
			glm::vec3 size = Rand3v(0.05f, 0.1f, 0.05f, 0.1f, 0.0f, 0.0f);

			GLColor rectangle_color;
			rectangle_color.Rand3f();

			auto rectangle = std::make_shared<RectangleObject>(
				this->transform, position, size, rectangle_color);
			this->children.push_back(rectangle);
		}
	}

	void OnMouseDown(int button, int x, int y) override
	{
		if (button == 0)
		{
			auto window_size = GLMain::GetInstance()->window->Size();
			auto mouse_position_world = glm::vec3(ScreenToWorldPoint(window_size, x, y), 0.0f);

			this->eraser->transform->position = mouse_position_world;

			this->eraser->visible = true;
		}
	}

	void OnMouseMove(int button, int x, int y) override
	{
		if (button == 0)
		{
			auto window_size = GLMain::GetInstance()->window->Size();
			auto mouse_position_world = glm::vec3(ScreenToWorldPoint(window_size, x, y), 0.0f);

			this->eraser->transform->position = mouse_position_world;

			auto& eraser_size = this->eraser->transform->scale;
			auto& eraser_position = this->eraser->transform->position;

			float eraser_min_x = eraser_position.x - eraser_size.x / 2.0f;
			float eraser_max_x = eraser_position.x + eraser_size.x / 2.0f;
			float eraser_min_y = eraser_position.y - eraser_size.y / 2.0f;
			float eraser_max_y = eraser_position.y + eraser_size.y / 2.0f;

			for (auto itr = this->children.begin() + 1; itr != this->children.end(); ++itr)
			{
				auto& size = (*itr)->transform->scale;
				auto& position = (*itr)->transform->position;

				float min_x = position.x - size.x / 2.0f;
				float max_x = position.x + size.x / 2.0f;
				float min_y = position.y - size.y / 2.0f;
				float max_y = position.y + size.y / 2.0f;

				if (!(eraser_max_x < min_x || eraser_min_x > max_x ||
					eraser_max_y < min_y || eraser_min_y > max_y))
				{
					this->children.erase(itr);
					break;
				}
			}
		}
	}

	void OnMouseUp(int button, int x, int y) override
	{
		if (button == 0)
		{
			this->eraser->visible = false;
		}
	}

	std::shared_ptr<RectangleObject> eraser;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training12");

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW Initialized" << std::endl;
	}

	GLMain::GetInstance()->window = window;

	auto scene = std::make_shared<GLScene>("Main");
	GLLoadScene(scene);

	scene->root->children.push_back(std::make_shared<RectangleCreator>(scene->root->transform));

	glutMainLoop();
}