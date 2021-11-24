#pragma once

#include <random>
#include <memory>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLColor.h"

void InitializeGLEW()
{
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW." << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "GLEW initialized." << std::endl;
	}
}

template <typename T>
T Rand(T min, T max)
{
	static std::default_random_engine engine((unsigned int)time(NULL));

	std::uniform_int_distribution<T> distribution(min, max);
	return distribution(engine);
}



GLfloat Rand(GLfloat min, GLfloat max)
{
	static std::default_random_engine engine((unsigned int)time(NULL));

	std::uniform_real_distribution<GLfloat> distribution(min, max);
	return distribution(engine);
}

GLdouble Rand(GLdouble min, GLdouble max)
{
	static std::default_random_engine engine((unsigned int)time(NULL));

	std::uniform_real_distribution<GLdouble> distribution(min, max);
	return distribution(engine);
}

template <typename T>
glm::tvec2<T> Rand2v(T minX, T maxX, T minY, T maxY)
{
	return glm::tvec2<T>(Rand(minX, maxX), Rand(minY, maxY));
}

template <typename T>
glm::tvec3<T> Rand3v(T minX, T maxX, T minY, T maxY, T minZ, T maxZ)
{
	return glm::tvec3<T>(Rand(minX, maxX), Rand(minY, maxY), Rand(minZ, maxZ));
}

template <typename T>
glm::tvec4<T> Rand4v(T minX, T maxX, T minY, T maxY, T minZ, T maxZ, T minW, T maxW)
{
	return glm::tvec4<T>(Rand(minX, maxX), Rand(minY, maxY), Rand(minZ, maxZ), Rand(minW, maxW));
}

int RandSign()
{
	int sign = Rand(0, 2);

	return sign == 0 ? -1 : 1;
}

GLColor RandColor3f()
{
	GLColor color;
	color.Rand3f();

	return color;
}

GLColor RandColor4f()
{
	GLColor color;
	color.Rand4f();

	return color;
}

void RandVertexColor3f(const GLSharedPtr<GLMesh>& mesh)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = RandColor3f();
	}
}

void RandVertexColor3f(GLMesh* mesh)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = RandColor3f();
	}
}

void RandVertexColor4f(const GLSharedPtr<GLMesh>& mesh)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = RandColor4f();
	}
}

void RandVertexColor4f(GLMesh* mesh)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = RandColor4f();
	}
}

void RandVertexColor3f(const GLSharedPtr<GLGameObject>& gameObject)
{
	RandVertexColor3f(gameObject->GetMeshRenderer()->GetMesh());
}

void RandVertexColor3f(GLGameObject* gameObject)
{
	RandVertexColor3f(gameObject->GetMeshRenderer()->GetMesh());
}

void RandVertexColor4f(const GLSharedPtr<GLGameObject>& gameObject)
{
	RandVertexColor4f(gameObject->GetMeshRenderer()->GetMesh());
}

void RandVertexColor4f(GLGameObject* gameObject)
{
	RandVertexColor4f(gameObject->GetMeshRenderer()->GetMesh());
}

void SetVertexColor(const GLSharedPtr<GLMesh>& mesh, GLColor color)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = color;
	}
}

void SetVertexColor(GLMesh* mesh, GLColor color)
{
	for (auto& vColor : mesh->GetColors())
	{
		vColor = color;
	}
}

void SetVertexColor(const GLSharedPtr<GLGameObject>& gameObject, GLColor color)
{
	SetVertexColor(gameObject->GetMeshRenderer()->GetMesh(), color);
}

void SetVertexColor(GLGameObject* gameObject, GLColor color)
{
	SetVertexColor(gameObject->GetMeshRenderer()->GetMesh(), color);
}

void RandMaterial(const GLSharedPtr<GLGameObject>& gameObject)
{
	auto material = gameObject->GetMeshRenderer()->GetMaterial();

	material->SetVector("ambient", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetVector("diffuse", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetVector("specular", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetFloat("shininess", Rand(0.0f, 128.0f));
}

void RandMaterial(GLGameObject* gameObject)
{
	auto material = gameObject->GetMeshRenderer()->GetMaterial();

	material->SetVector("ambient", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetVector("diffuse", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetVector("specular", Rand3v(0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f));
	material->SetFloat("shininess", Rand(0.0f, 128.0f));
}