#pragma once

#include <memory>

#include <gl/glew.h>

#include "GLTransform.h"
#include "GLShader.h"
#include "GLMesh.h"

class GLMeshRenderer
{
public:
	GLMeshRenderer(const std::shared_ptr<GLTransform>& transform) 
		: transform(transform)
	{
		this->mesh = std::make_shared<GLMesh>();
		this->shader = GLShader::GetDefaultShader();
	}

	void Render()
	{
		if (this->transform == nullptr)
		{
			return;
		}

		this->shader->Use();
		this->mesh->Render(*this->transform);
	}

	std::shared_ptr<GLMesh> mesh = nullptr;
	std::shared_ptr<GLShader> shader = nullptr;

	std::shared_ptr<GLTransform> transform = nullptr;
};