#pragma once

#include <string>
#include <unordered_map>

#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLShader.h"
#include "GLBasicShader.h"
#include "GLTexture.h"



class GLMaterial
{
public:
	GLMaterial()
	{
		this->shader = GLCreate<GLBasicMaterialShader>();
	}

	GLMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
	{
		this->shader = GLCreate<GLBasicMaterialShader>();

		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
	}

	virtual ~GLMaterial()
	{

	}

	glm::vec3 GetAmbient()
	{
		return this->ambient;
	}

	glm::vec3 GetDiffuse()
	{
		return this->diffuse;
	}

	glm::vec3 GetSpecular()
	{
		return this->specular;
	}

	float GetShininess()
	{
		return this->shininess;
	}

	void SetAmbient(const glm::vec3& ambient)
	{
		this->ambient = ambient;
	}

	void SetDiffuse(const glm::vec3& diffuse)
	{
		this->diffuse = diffuse;
	}

	void SetSpecular(const glm::vec3& specular)
	{
		this->specular = specular;
	}

	void SetShininess(float shininess)
	{
		this->shininess = shininess;
	}

	GLSharedPtr<GLShader> GetShader()
	{
		return this->shader;
	}

	void SetShader(const GLSharedPtr<GLShader>& shader)
	{
		this->shader = shader;
	}

	GLSharedPtr<GLTexture> GetDiffuseMap()
	{
		return this->diffuseMap;
	}

	void SetDiffuseMap(const GLSharedPtr<GLTexture>& diffuseMap)
	{
		if (this->diffuseMap == nullptr && diffuseMap != nullptr)
		{
			this->shader = GLCreate<GLBasicTextureMaterialShader>();
		}
		else if (diffuseMap == nullptr)
		{
			this->shader = GLCreate<GLBasicMaterialShader>();
		}

		this->diffuseMap = diffuseMap;
	}

	void Use()
	{
		this->shader->Use();

		int ambientUniform = this->shader->GetUniformLocation("material.ambient");
		int diffuseUniform = this->shader->GetUniformLocation("material.diffuse");
		int specularUniform = this->shader->GetUniformLocation("material.specular");
		int shininessUniform = this->shader->GetUniformLocation("material.shininess");

		if (this->diffuseMap != nullptr)
		{
			this->shader->SetUniform("material.diffuse", 0);
			this->diffuseMap->Use();
		}
		else
		{
			if (ambientUniform > 0)
			{
				this->shader->SetUniform(ambientUniform, this->ambient);
			}

			if (diffuseUniform > 0)
			{
				this->shader->SetUniform(diffuseUniform, this->diffuse);
			}
		}

		if (specularUniform > 0)
		{
			this->shader->SetUniform(specularUniform, this->specular);
		}

		if (shininessUniform > 0)
		{
			this->shader->SetUniform(shininessUniform, this->shininess);
		}
	}

private:
	glm::vec3 ambient = glm::vec3(1.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float shininess = 0.0f;

	GLSharedPtr<GLShader> shader = nullptr;
	GLSharedPtr<GLTexture> diffuseMap = nullptr;
};

std::unordered_map<std::string, GLSharedPtr<GLMaterial>> __GLPredefinedMaterials;

GLSharedPtr<GLMaterial> GLGetPreDefinedMaterial(const std::string& materialType)
{
	if (__GLPredefinedMaterials.size() == 0)
	{
		__GLPredefinedMaterials["Emerald"] = GLCreate<GLMaterial>(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633f), 0.6f);
		__GLPredefinedMaterials["Jade"] = GLCreate<GLMaterial>(glm::vec3(0.135f, 0.2225f, 0.1575f), glm::vec3(0.54f, 0.89f, 0.63f), glm::vec3(0.316228f, 0.316228f, 0.316228f), 0.1f);
		__GLPredefinedMaterials["Obsidian"] = GLCreate<GLMaterial>(glm::vec3(0.05375f, 0.05f, 0.06625f), glm::vec3(0.18275f, 0.17f, 0.22525f), glm::vec3(0.332741f, 0.328634f, 0.346435f), 0.3f);
		__GLPredefinedMaterials["Pearl"] = GLCreate<GLMaterial>(glm::vec3(0.25f, 0.20725f, 0.20725f), glm::vec3(1.0f, 0.829f, 0.829f), glm::vec3(0.296648f, 0.296648f, 0.296648f), 0.088f);
		__GLPredefinedMaterials["Ruby"] = GLCreate<GLMaterial>(glm::vec3(0.1745f, 0.01175f, 0.01175f), glm::vec3(0.61424f, 0.04136f, 0.04136f), glm::vec3(0.727811f, 0.626959f, 0.626959f), 0.6f);
		__GLPredefinedMaterials["Turquoise"] = GLCreate<GLMaterial>(glm::vec3(0.1f, 0.18725f, 0.1745f), glm::vec3(0.396f, 0.74151f, 0.69102f), glm::vec3(0.297254f, 0.30829f, 0.306678f), 0.1f);
		__GLPredefinedMaterials["Brass"] = GLCreate<GLMaterial>(glm::vec3(0.329412f, 0.223529f, 0.027451f), glm::vec3(0.780392f, 0.568627f, 0.113725f), glm::vec3(0.992157f, 0.941176f, 0.807843f), 0.21794872f);
		__GLPredefinedMaterials["Bronze"] = GLCreate<GLMaterial>(glm::vec3(0.2125f, 0.1275f, 0.054f), glm::vec3(0.714f, 0.4284f, 0.18144f), glm::vec3(0.393548f, 0.271906f, 0.166721f), 0.2f);
		__GLPredefinedMaterials["Chrome"] = GLCreate<GLMaterial>(glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.774597f, 0.774597f, 0.774597f), 0.6f);
		__GLPredefinedMaterials["Copper"] = GLCreate<GLMaterial>(glm::vec3(0.19125f, 0.0735f, 0.0225f), glm::vec3(0.7038f, 0.27048f, 0.0828f), glm::vec3(0.256777f, 0.137622f, 0.086014f), 0.1f);
		__GLPredefinedMaterials["Gold"] = GLCreate<GLMaterial>(glm::vec3(0.24725f, 0.1995f, 0.0745f), glm::vec3(0.75164f, 0.60648f, 0.22648f), glm::vec3(0.628281f, 0.555802f, 0.366065f), 0.4f);
		__GLPredefinedMaterials["Silver"] = GLCreate<GLMaterial>(glm::vec3(0.19225f, 0.19225f, 0.19225f), glm::vec3(0.50754f, 0.50754f, 0.50754f), glm::vec3(0.508273f, 0.508273f, 0.508273f), 0.4f);
		__GLPredefinedMaterials["BlackPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.50f, 0.50f, 0.50f), 0.25f);
		__GLPredefinedMaterials["CyanPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 0.25f);
		__GLPredefinedMaterials["GreenPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.35f, 0.1f), glm::vec3(0.45f, 0.55f, 0.45f), 0.25f);
		__GLPredefinedMaterials["RedPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(0.7f, 0.6f, 0.6f), 0.25f);
		__GLPredefinedMaterials["WhitePlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.55f, 0.55f, 0.55f), glm::vec3(0.70f, 0.70f, 0.70f), 0.25f);
		__GLPredefinedMaterials["YellowPlastic"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.60f, 0.60f, 0.50f), 0.25f);
		__GLPredefinedMaterials["BlackRubber"] = GLCreate<GLMaterial>(glm::vec3(0.02f, 0.02f, 0.02f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.4f, 0.4f, 0.4f), 0.078125f);
		__GLPredefinedMaterials["CyanRubber"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.05f, 0.05f), glm::vec3(0.4f, 0.5f, 0.5f), glm::vec3(0.04f, 0.7f, 0.7f), 0.078125f);
		__GLPredefinedMaterials["GreenRubber"] = GLCreate<GLMaterial>(glm::vec3(0.0f, 0.05f, 0.0f), glm::vec3(0.4f, 0.5f, 0.4f), glm::vec3(0.04f, 0.7f, 0.04f), 0.078125f);
		__GLPredefinedMaterials["RedRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.0f, 0.0f), glm::vec3(0.5f, 0.4f, 0.4f), glm::vec3(0.7f, 0.04f, 0.04f), 0.078125f);
		__GLPredefinedMaterials["WhiteRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.7f, 0.7f), 0.078125f);
		__GLPredefinedMaterials["YellowRubber"] = GLCreate<GLMaterial>(glm::vec3(0.05f, 0.05f, 0.0f), glm::vec3(0.5f, 0.5f, 0.4f), glm::vec3(0.7f, 0.7f, 0.04f), 0.078125f);
	}

	return __GLPredefinedMaterials[materialType];
}