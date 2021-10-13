#include <iostream>
#include <memory>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "../GL/GL.h"

class TransformableObject : public GLGameObject
{
public:
	TransformableObject(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		this->cube_mesh = std::make_shared<GLCubeMesh>();
		this->triangular_pyramid_mesh = std::make_shared<GLConeMesh>(3);

		for (auto i = 0; i < cube_mesh->vertices.size(); ++i)
		{
			GLColor color;
			color.Rand3f();
			this->cube_mesh->vertices[i].color = color;
		}

		for (auto i = 0; i < this->triangular_pyramid_mesh->vertices.size(); ++i)
		{
			GLColor color;
			color.Rand3f();
			this->triangular_pyramid_mesh->vertices[i].color = color;
		}

		this->mesh_renderer->mesh = this->cube_mesh;

		this->transform->Rotate(glm::radians(30.0f), glm::radians(-30.0f), 0.0f);

		glEnable(GL_DEPTH_TEST);
	}

	void OnKeyDown(const std::string& key, int x, int y) override
	{
		if (key == "1")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 1, 2, 1, 2, 3 });
		}
		else if (key == "2")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 4, 5, 6, 5, 6, 7 });
		}
		else if (key == "3")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 2, 4, 2, 4, 6 });
		}
		else if (key == "4")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 1, 3, 5, 3, 5, 7 });
		}
		else if (key == "5")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 1, 4, 1, 4, 5 });
		}
		else if (key == "6")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 2, 3, 6, 3, 6, 7 });
		}
		else if (key == "7")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 1, 2, 3 });
		}
		else if (key == "8")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 0, 1, 2 });
		}
		else if (key == "9")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 0, 2, 3 });
		}
		else if (key == "0")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 0, 3, 1 });
		}
		else if (key == "a")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 });
		}
		else if (key == "b")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 2, 4, 2, 4, 6, 1, 3, 5, 3, 5, 7 });
		}
		else if (key == "c")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), { 0, 1, 4, 1, 4, 5, 2, 3, 6, 3, 6, 7 });
		}
		else if (key == "e")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 1, 2, 3, 0, 1, 2 });
		}
		else if (key == "f")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 1, 2, 3, 0, 2, 3 });
		}
		else if (key == "g")
		{
			this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
			this->triangular_pyramid_mesh->indices.clear();
			this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 1, 2, 3, 0, 3, 1 });
		}
		else if (key == "h")
		{
			this->mesh_renderer->mesh = this->cube_mesh;
			this->cube_mesh->indices.clear();
			this->cube_mesh->indices.insert(this->cube_mesh->indices.end(), {
				0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7,
				0, 2, 4, 2, 4, 6, 1, 3, 5, 3, 5, 7,
		        0, 1, 4, 1, 4, 5, 2, 3, 6, 3, 6, 7
			});
		}
		else if (key == "i")
		{
		    this->mesh_renderer->mesh = this->triangular_pyramid_mesh;
    		this->triangular_pyramid_mesh->indices.clear();
	    	this->triangular_pyramid_mesh->indices.insert(this->triangular_pyramid_mesh->indices.end(), { 
				1, 2, 3, 0, 1, 2, 0, 2, 3, 0, 3, 1
			});
		}

	}

	std::shared_ptr<GLMesh> cube_mesh;
	std::shared_ptr<GLMesh> triangular_pyramid_mesh;
};

class AxisObject : public GLGameObject
{
public:
	AxisObject(const std::shared_ptr<GLTransform>& parent)
		: GLGameObject(parent)
	{
		auto axis_mesh = std::make_shared<GLAxis3DMesh>();
		this->mesh_renderer->mesh = axis_mesh;

		for (auto i = 0; i < axis_mesh->vertices.size(); ++i)
		{
			axis_mesh->vertices[i].color = GLColor(0.0f, 0.0f, 0.0f);
		}

		this->transform->SetScale(3.0f, 3.0f, 3.0f);
	}
};

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	auto window = std::make_shared<GLWindow>(0, 0, 800, 800, "Training13");

	InitializeGLEW();

	GLMain::GetInstance()->window = window;

	auto scene = std::make_shared<GLScene>("Training13");
	auto camera = std::make_shared<GLCamera>(scene->root->transform, 800, 800, 90.0f);
	camera->transform->Translate(0.0f, 0.0f, 1.5f);

	scene->active_camera = camera;

	GLLoadScene(scene);

	scene->root->children.push_back(std::make_shared<TransformableObject>(scene->root->transform));
	scene->root->children.push_back(std::make_shared<AxisObject>(scene->root->transform));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);

	glutMainLoop();
}