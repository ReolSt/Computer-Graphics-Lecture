#pragma once

#include <string>
#include <unordered_map>

#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLColor.h"
#include "GLShader.h"
#include "GLBasicShader.h"

class GLMaterial
{
public:
	GLMaterial()
	{
		this->shader = GLCreate<GLBasicMaterialShader>();

		this->vectors["ambient"] = glm::vec3(1.0f);
		this->vectors["diffuse"] = glm::vec3(1.0f);
		this->vectors["specular"] = glm::vec3(1.0f);
		this->floats["shininess"] = 1.0f;
	}

	GLMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
	{
		this->vectors["ambient"] = ambient;
		this->vectors["diffuse"] = diffuse;
		this->vectors["specular"] = specular;
		this->floats["shininess"] = shininess;
	}

	virtual ~GLMaterial()
	{

	}

	GLSharedPtr<GLShader> GetShader()
	{
		return this->shader;
	}

	void SetShader(const GLSharedPtr<GLShader>& shader)
	{
		this->shader = shader;
	}

	void Use()
	{
		this->shader->Use();

		for (const auto& item : this->ints)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->floats)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->vectors)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}

		for (const auto& item : this->matrices)
		{
			std::string name = "material." + item.first;
			if (this->shader->GetUniformLocation(name) > 0)
			{
				this->shader->SetUniform(name, item.second);
			}
		}
	}

	int GetInt(const std::string& name)
	{
		assert(this->ints.find(name) != this->ints.end());

		return this->ints[name];
	}
	
	void SetInt(const std::string& name, int value)
	{
		this->ints[name] = value;
	}

	float GetFloat(const std::string& name)
	{
		assert(this->floats.find(name) != this->floats.end());

		return this->floats[name];
	}

	void SetFloat(const std::string& name, float value)
	{
		this->floats[name] = value;
	}

	glm::vec3 GetVector(const std::string& name)
	{
		assert(this->vectors.find(name) != this->vectors.end());

		return this->vectors[name];
	}

	void SetVector(const std::string& name, const glm::vec3& value)
	{
		this->vectors[name] = value;
	}

	glm::mat4 GetMatrix(const std::string& name)
	{
		assert(this->matrices.find(name) != this->matrices.end());

		return this->matrices[name];
	}

	void SetMatrix(const std::string & name, const glm::mat4& matrix)
	{
		this->matrices[name] = matrix;
	}

private:
	std::unordered_map<std::string, int> ints;
	std::unordered_map<std::string, float> floats;
	std::unordered_map<std::string, glm::vec3> vectors;
	std::unordered_map<std::string, glm::mat4> matrices;

	GLSharedPtr<GLShader> shader;
};