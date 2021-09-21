#include <iostream>
#include <memory>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GL.h"

class LineToTriangle : public GLGameObject
{
public:
	LineToTriangle(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLColor blue(0.0f, 0.0f, 1.0f);

		GLTriangle triangle
		(
			{glm::vec3(-0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f)},
			{blue, blue, blue}
		);

		this->mesh_renderer->mesh->triangles.push_back(triangle);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		auto& transition_point = this->mesh_renderer->mesh->triangles[0].v3;
		if (transition_point.position.x > 0.2f)
		{
			this->transition = false;
			transition_point.position = glm::vec3(0.2f, -0.2f, 0.0f);
		}

		if(this->transition)
		{
			transition_point.position.x += step_size;
			transition_point.position.y -= step_size * 2.0f;
		}
	}

	float step_size = 0.001f;

	bool transition = true;
};

class TriangleToRectangle : public GLGameObject
{
public:
	TriangleToRectangle(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLColor yellow(1.0f, 1.0f, 0.0f);

		GLTriangle triangleA
		(
			{ glm::vec3(-0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.2f, -0.2f, 0.0f) },
			{ yellow, yellow, yellow }
		);

		GLTriangle triangleB
		(
			{ glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f) },
		    { yellow, yellow, yellow }
		);

		this->mesh_renderer->mesh->triangles.push_back(triangleA);
		this->mesh_renderer->mesh->triangles.push_back(triangleB);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		auto& transition_pointA = this->mesh_renderer->mesh->triangles[0].v2;
		auto& transition_pointB = this->mesh_renderer->mesh->triangles[1].v1;
		auto& transition_pointC = this->mesh_renderer->mesh->triangles[1].v3;
		if (transition_pointA.position.x < -0.2f)
		{
			this->transition = false;
			transition_pointA.position = glm::vec3(-0.2f, 0.2f, 0.0f);
			transition_pointB.position = glm::vec3(-0.2f, 0.2f, 0.0f);
			transition_pointC.position = glm::vec3(0.2f, 0.2f, 0.0f);
		}

		if (this->transition)
		{
			transition_pointA.position.x -= step_size;
			transition_pointB.position.x -= step_size;
			transition_pointC.position.x += step_size;
		}
	}

	float step_size = 0.001f;

	bool transition = true;
};

class RectangleToPentagon : public GLGameObject
{
public:
	RectangleToPentagon(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLColor green(0.0f, 1.0f, 0.0f);

		GLTriangle triangleA
		(
			{ glm::vec3(-0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.2f, -0.2f, 0.0f) },
			{ green, green, green }
		);		

		GLTriangle triangleB
		(
			{ glm::vec3(-0.2f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(-0.2f, -0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleC
		(
			{ glm::vec3(0.2f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.2f, -0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleD
		(
			{ glm::vec3(-0.2f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleE
		(
			{ glm::vec3(0.2f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f) },
			{ green, green, green }
		);

		this->mesh_renderer->mesh->triangles.push_back(triangleA);
		this->mesh_renderer->mesh->triangles.push_back(triangleB);
		this->mesh_renderer->mesh->triangles.push_back(triangleC);
		this->mesh_renderer->mesh->triangles.push_back(triangleD);
		this->mesh_renderer->mesh->triangles.push_back(triangleE);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);

		auto& triangles = this->mesh_renderer->mesh->triangles;

		std::array<float*, 15> transition_targets =
		{
			&triangles[0].v1.position.x,
			&triangles[0].v2.position.y,
			&triangles[0].v3.position.x,
			&triangles[1].v1.position.y,
			&triangles[1].v2.position.y,
			&triangles[1].v3.position.x,
			&triangles[2].v1.position.y,
			&triangles[2].v2.position.y,
			&triangles[2].v3.position.x,
			&triangles[3].v1.position.y,
			&triangles[3].v2.position.y,
			&triangles[3].v3.position.y,
			&triangles[4].v1.position.y,
			&triangles[4].v2.position.y,
			&triangles[4].v3.position.y
		};

		std::array<float, 15> transition_multiplier
		{
			0.5f,
			-1.0f,
			-0.5f,
			-1.0f,
			-1.0f,
			0.5f,
			-1.0f,
			-1.0f,
			-0.5f,
			-1.0f,
			-1.0f,
			1.0f,
			-1.0f,
			-1.0f,
			1.0f
		};

		if (*transition_targets[0] > -0.15f)
		{
			this->transition = false;
			*transition_targets[0] = -0.15f;
			*transition_targets[1] = 0.10f;
			*transition_targets[2] = 0.15f;
			*transition_targets[3] = 0.10f;
			*transition_targets[4] = 0.10f;
			*transition_targets[5] = -0.15f;
			*transition_targets[6] = 0.10f;
			*transition_targets[7] = 0.10f;
			*transition_targets[8] = 0.15f;
			*transition_targets[9] = 0.10f;
			*transition_targets[10] = 0.10f;
			*transition_targets[11] = 0.30f;
			*transition_targets[12] = 0.10f;
			*transition_targets[13] = 0.10f;
			*transition_targets[14] = 0.30f;
		}

		if (this->transition)
		{
			for (int i = 0; i < 15; ++i)
			{
				*transition_targets[i] += transition_multiplier[i] * this->step_size;
			}
		}
	}

	float step_size = 0.001f;

	bool transition = true;
};

class PentagonToPoint : public GLGameObject
{
public:
	PentagonToPoint(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLColor green(1.0f, 0.0f, 1.0f);

		GLTriangle triangleA
		(
			{ glm::vec3(-0.15f, -0.2f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.15f, -0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleB
		(
			{ glm::vec3(-0.2f, 0.1f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(-0.15f, -0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleC
		(
			{ glm::vec3(0.2f, 0.1f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.15f, -0.2f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleD
		(
			{ glm::vec3(-0.2f, 0.1f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 0.3f, 0.0f) },
			{ green, green, green }
		);

		GLTriangle triangleE
		(
			{ glm::vec3(0.2f, 0.1f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(0.0f, 0.3f, 0.0f) },
			{ green, green, green }
		);

		this->mesh_renderer->mesh->triangles.push_back(triangleA);
		this->mesh_renderer->mesh->triangles.push_back(triangleB);
		this->mesh_renderer->mesh->triangles.push_back(triangleC);
		this->mesh_renderer->mesh->triangles.push_back(triangleD);
		this->mesh_renderer->mesh->triangles.push_back(triangleE);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);


		if (this->transform->scale.x < 0.05f)
		{
			this->transition = false;
			this->transform->scale = glm::vec3(0.05f, 0.05f, 0.05f);
		}

		if (this->transition)
		{
			this->transform->scale -= step_size;
		}
	}

	float speed = 1.0f;
	float step_size = 0.004f;

	bool transition = true;
};



class TransitionDisplayer : public GLGameObject
{
public:
	TransitionDisplayer(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		GLColor white(1.0f, 1.0f, 1.0f);
		GLLine vertical_line({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f) }, { white, white });
		GLLine horizontal_line({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f) }, { white, white });

		this->mesh_renderer->mesh->lines.push_back(vertical_line);
		this->mesh_renderer->mesh->lines.push_back(horizontal_line);

		this->CreateTransitions();
	}

	void CreateTransitions()
	{
		auto transitionA = std::make_shared<LineToTriangle>(this->transform);
		auto transitionB = std::make_shared<TriangleToRectangle>(this->transform);
		auto transitionC = std::make_shared<RectangleToPentagon>(this->transform);
		auto transitionD = std::make_shared<PentagonToPoint>(this->transform);

		transitionA->transform->position = glm::vec3(-0.5f, 0.5f, 0.0f);
		transitionB->transform->position = glm::vec3(0.5f, 0.5f, 0.0f);
		transitionC->transform->position = glm::vec3(-0.5f, -0.5f, 0.0f);
		transitionD->transform->position = glm::vec3(0.5f, -0.5f, 0.0f);

		this->children.clear();

		this->children.push_back(transitionA);
		this->children.push_back(transitionB);
		this->children.push_back(transitionC);
		this->children.push_back(transitionD);
	}

	void Update(float delta_time) override
	{
		GLGameObject::Update(delta_time);
	}

	void OnMouseDown(int button, int x, int y)
	{
		if (button == 0)
		{
			this->CreateTransitions();
		}
	}
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 600, "Training10");

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

	auto scene = std::make_shared<GLScene>("Training10");
    GLLoadScene(scene);

	scene->root->children.push_back(std::make_shared<TransitionDisplayer>(scene->root->transform));
	scene->background = GLColor(0.0f, 0.0f, 0.0f);

	glutMainLoop();
}