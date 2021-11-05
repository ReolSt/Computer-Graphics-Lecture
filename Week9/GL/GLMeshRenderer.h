#pragma once

#include <memory>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLTransform.h"
#include "GLShader.h"
#include "GLMesh.h"

class GLMeshRenderer
{
public:
	GLMeshRenderer() 
	{
		this->Mesh = std::make_shared<GLMesh>();
		this->Shader = GLShader::GetDefaultShader();
	}

	void Update()
	{
		this->Mesh->Update();
	}

	void Render(const glm::mat4& modelMatrix, const glm::mat4& cameraMatrix)
	{
		this->Shader->Use();
		this->Shader->SetUniform("modelMatrix", modelMatrix);
		this->Shader->SetUniform("cameraMatrix", cameraMatrix);

		this->Mesh->Render();
	}

	GLSharedPtr<GLMesh> Mesh = nullptr;
	GLSharedPtr<GLShader> Shader = nullptr;
};