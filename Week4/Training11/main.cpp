#include <iostream>
#include <limits>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GL.h"

float GetDelta(const glm::vec3& v1, const glm::vec3& v2)
{
	float dividend = v2.y - v1.y;
	float divisor = v2.x - v1.x;

	if (divisor == 0.0f)
	{
		return std::numeric_limits<float>().max() * glm::sign(v2.y - v1.y);
	}

	return dividend / divisor;
}

float GetDeltaInverse(const glm::vec3& v1, const glm::vec3& v2)
{
	float dividend = v2.x - v1.x;
	float divisor = v2.y - v1.y;

	if (divisor == 0.0f)
	{
		return std::numeric_limits<float>().max() * glm::sign(v2.x - v1.x);
	}

	return dividend / divisor;
}

class TransformableRectangle : public GLGameObject
{
public:
	TransformableRectangle(std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->center = glm::vec3(0.0f, 0.0f, 0.0f);

		this->left_top = glm::vec3(-0.5f, 0.5f, 0.0f);
		this->left_bottom = glm::vec3(-0.5f, -0.5f, 0.0f);
		this->right_top = glm::vec3(0.5f, 0.5f, 0.0f);
		this->right_bottom = glm::vec3(0.5f, -0.5f, 0.0f);

		this->RefreshMesh();
	}

	void RefreshMesh()
	{
		GLPoint center(this->center, GLColor(0.0f, 0.0f, 0.0f));

		GLLine left(
			GLPoint(this->left_top, GLColor(1.0f, 0.0f, 0.0f)),
			GLPoint(this->left_bottom, GLColor(0.0f, 1.0f, 1.0f))
		);

		GLLine right(
			GLPoint(this->right_top, GLColor(1.0f, 1.0f, 0.0f)),
			GLPoint(this->right_bottom, GLColor(0.0f, 0.0f, 1.0f))
		);

		GLLine top(
			GLPoint(this->left_top, GLColor(0.1f, 0.1f, 0.1f)),
			GLPoint(this->right_top, GLColor(1.0f, 1.0f, 1.0f))
		);

		GLLine bottom(
			GLPoint(this->left_bottom, GLColor(0.0f, 1.0f, 0.0f)),
			GLPoint(this->right_bottom, GLColor(1.0f, 0.0f, 1.0f))
		);

		auto& mesh = this->mesh_renderer->mesh;
		mesh->points.clear();
		mesh->lines.clear();

		mesh->points.push_back(center);
		mesh->lines.push_back(left);
		mesh->lines.push_back(right);
		mesh->lines.push_back(top);
		mesh->lines.push_back(bottom);
	}

	void OnMouseDown(int button, int x, int y) override
	{
		auto window_size = GLMain::GetInstance()->window->Size();

		auto mouse_world_position = glm::vec3(ScreenToWorldPoint(window_size, x, y), 0.0f);

		auto left_top = glm::vec3(GLTransform::ApplyTransform(*this->transform, this->left_top));
		auto right_top = glm::vec3(GLTransform::ApplyTransform(*this->transform, this->right_top));
		auto left_bottom = glm::vec3(GLTransform::ApplyTransform(*this->transform, this->left_bottom));
		auto right_bottom = glm::vec3(GLTransform::ApplyTransform(*this->transform, this->right_bottom));

		std::array<float, 4> distances = {
			glm::distance2(left_top, mouse_world_position),
			glm::distance2(left_bottom, mouse_world_position),
			glm::distance2(right_top, mouse_world_position),
			glm::distance2(right_bottom, mouse_world_position)
		};

		int argmin = 0;
		float min = distances[0];

		for (auto i = 0; i < distances.size(); ++i)
		{
			if (distances[i] < min)
			{
				argmin = i;
				min = distances[i];
			}
		}

		if (min <= this->drag_distance_threshold)
		{
			this->drag_target = argmin;
		}
		else
		{
			auto left_delta_inverse = GetDeltaInverse(left_top, left_bottom);
			auto right_delta_inverse = GetDeltaInverse(right_top, right_bottom);
			auto top_delta_inverse = GetDeltaInverse(left_top, right_top);
			auto bottom_delta_inverse = GetDeltaInverse(left_bottom, right_bottom);

			std::array<std::array<float, 2>, 4> ranges = {
				std::array<float, 2>{left_bottom.x, left_top.x},
				std::array<float, 2>{right_bottom.x, right_top.x},
				std::array<float, 2>{left_top.x, right_top.x},
				std::array<float, 2>{left_bottom.x, right_bottom.x}
			};

			std::array<float, 4> crosses = {
				left_delta_inverse * (mouse_world_position.y - left_top.y) + left_top.x,
				right_delta_inverse * (mouse_world_position.y - right_top.y) + right_top.x,
				top_delta_inverse * (mouse_world_position.y - left_top.y) + left_top.x,
				bottom_delta_inverse * (mouse_world_position.y - left_bottom.y) + left_bottom.x
			};

			int cross_cnt = 0;
			for (auto i = 0; i < crosses.size(); ++i)
			{
				float left = glm::min(ranges[i][0], ranges[i][1]);
				float right = glm::max(ranges[i][0], ranges[i][1]);
				if (crosses[i] < left || crosses[i] > right)
				{
					continue;
				}

				if (crosses[i] > mouse_world_position.x)
				{
					++cross_cnt;
				}
			}

			if (cross_cnt % 2)
			{
				this->drag_target = 4;
			}
		}
	}

	void OnMouseUp(int button, int x, int y) override
	{
		if (button == 0)
		{
			this->drag_target = -1;
		}
	}

	void OnMouseMove(int button, int x, int y) override
	{
		static int px = x;
		static int py = y;

		if (button == 0)
		{
			auto window_size = GLMain::GetInstance()->window->Size();

			auto mouse_world_position = glm::vec3(ScreenToWorldPoint(window_size, x, y), 0.0f);
			auto mouse_world_previous = glm::vec3(ScreenToWorldPoint(window_size, px, py), 0.0f);
			auto mouse_world_delta = mouse_world_position - mouse_world_previous;

			switch (this->drag_target)
			{
			case 0:
				this->left_top += mouse_world_delta;
				break;
			case 1:
				this->left_bottom += mouse_world_delta;
				break;
			case 2:
				this->right_top += mouse_world_delta;
				break;
			case 3:
				this->right_bottom += mouse_world_delta;
				break;
			case 4:
				this->transform->Translate(mouse_world_delta);
			}

			this->RefreshMesh();
		}

		px = x;
		py = y;

	}
private:
	glm::vec3 center;
	glm::vec3 left_top;
	glm::vec3 left_bottom;
	glm::vec3 right_top;
	glm::vec3 right_bottom;

	float drag_distance_threshold = 0.01f;
	int drag_target = -1;
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training11");

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

	scene->root->children.push_back(std::make_shared<TransformableRectangle>(scene->root->transform));

	glutMainLoop();
}