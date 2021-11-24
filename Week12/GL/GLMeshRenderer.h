#pragma once

#include <memory>

#include <gl/glew.h>
#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLTransform.h"
#include "GLShader.h"
#include "GLMesh.h"
#include "GLMaterial.h"
#include "GLLight.h"

#define MAX_DIRECTIONAL_LIGHT_COUNT 16
#define MAX_POINT_LIGHT_COUNT 16
#define MAX_SPOT_LIGHT_COUNT 16

class GLMeshRenderer
{
public:
	GLMeshRenderer() 
	{
		this->mesh = std::make_shared<GLMesh>();
		this->material = GLCreate<GLMaterial>();
	}

	~GLMeshRenderer()
	{
		this->mesh = nullptr;
		this->material = nullptr;
	}

	void Update()
	{
		this->mesh->Update();
	}

	void Render(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPosition)
	{
		this->material->Use();

		auto shader = this->material->GetShader();

		shader->SetUniform("model", modelMatrix);
		shader->SetUniform("view", viewMatrix);
		shader->SetUniform("projection", projectionMatrix);
		shader->SetUniform("viewPosition", cameraPosition);

		this->mesh->Render();
	}

	void Render(const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const glm::vec3 cameraPosition,
		        const std::vector<GLSharedPtr<GLLight>>& lights)
	{
		this->material->Use();

		auto shader = this->material->GetShader();

		shader->SetUniform("model", modelMatrix);
		shader->SetUniform("view", viewMatrix);
		shader->SetUniform("projection", projectionMatrix);
		shader->SetUniform("cameraPosition", cameraPosition);

		int directionalCount = 0;
		int pointCount = 0;
		int spotCount = 0;

		for (int i = 0; i < lights.size(); ++i)
		{
			auto directionalLight = std::dynamic_pointer_cast<GLDirectionalLight>(lights[i]);
			if (directionalLight != nullptr && directionalLight->GetActive())
			{
				directionalLight->Apply(shader, directionalCount++);
			}

			auto pointLight = std::dynamic_pointer_cast<GLPointLight>(lights[i]);
			if (pointLight != nullptr && pointLight->GetActive())
			{
				pointLight->Apply(shader, pointCount++);
			}

			auto spotLight = std::dynamic_pointer_cast<GLSpotLight>(lights[i]);
			if (spotLight != nullptr && spotLight->GetActive())
			{
				spotLight->Apply(shader, spotCount++);
			}
		}

		shader->SetUniform("directionalLightCount", directionalCount);
		shader->SetUniform("pointLightCount", pointCount);
		shader->SetUniform("spotLightCount", spotCount);

		this->mesh->Render();
	}

	GLSharedPtr<GLMesh>& GetMesh()
	{
		return this->mesh;
	}

	GLSharedPtr<GLMaterial>& GetMaterial()
	{
		return this->material;
	}

	void SetMesh(const GLSharedPtr<GLMesh>& mesh)
	{
		this->mesh = mesh;
	}

	void SetMaterial(const GLSharedPtr<GLMaterial>& material)
	{
		this->material = material;
	}

private:
	GLSharedPtr<GLMesh> mesh = nullptr;
	GLSharedPtr<GLMaterial> material = nullptr;
};