#pragma once

#include <gl/glm/glm.hpp>

class GLLight
{
public:
	GLLight()
	{

	}

	virtual ~GLLight()
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

	virtual void Apply(const GLSharedPtr<GLShader>& shader, int index) = 0;

	template <typename T>
	void ApplyUniform(const GLSharedPtr<GLShader>& shader, const std::string& name, T value)
	{
		int location = shader->GetUniformLocation(name);

		if (location >= 0)
		{
			shader->SetUniform(location, value);
		}
	}

	bool GetActive()
	{
		return this->bIsActive;
	}

	void SetActive(bool active)
	{
		this->bIsActive = active;
	}

private:
	glm::vec3 ambient = glm::vec3(1.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);

	bool bIsActive = true;
};

class GLDirectionalLight : public GLLight
{
public:
	GLDirectionalLight()
	{

	}

	~GLDirectionalLight()
	{

	}

	void Apply(const GLSharedPtr<GLShader>& shader, int index) override
	{
		if (!this->GetActive())
		{
			return;
		}

		std::string prefix = "directionalLights[" + std::to_string(index) + "]";

		std::string ambientUniformName = prefix + "." + "ambient";
		std::string diffuseUniformName = prefix + "." + "diffuse";
		std::string specularUniformName = prefix + "." + "specular";
		std::string directionUniformName = prefix + "." + "direction";

		this->ApplyUniform(shader, ambientUniformName, this->GetAmbient());
		this->ApplyUniform(shader, diffuseUniformName, this->GetDiffuse());
		this->ApplyUniform(shader, specularUniformName, this->GetSpecular());
		this->ApplyUniform(shader, directionUniformName, this->GetDirection());
	}

	glm::vec3 GetDirection()
	{
		return this->direction;
	}

	void SetDirection(const glm::vec3& direction)
	{
		this->direction = direction;
	}

private:
	glm::vec3 direction = glm::vec3(0.0f);
};

class GLPointLight : public GLLight
{
public:
	GLPointLight()
	{

	}

	~GLPointLight()
	{

	}

	void Apply(const GLSharedPtr<GLShader>& shader, int index)
	{
		if (!this->GetActive())
		{
			return;
		}

		std::string prefix = "pointLights[" + std::to_string(index) + "]";

		std::string ambientUniformName = prefix + "." + "ambient";
		std::string diffuseUniformName = prefix + "." + "diffuse";
		std::string specularUniformName = prefix + "." + "specular";
		std::string positionUniformName = prefix + "." + "position";
		std::string constantUniformName = prefix + "." + "constant";
		std::string linearUniformName = prefix + "." + "linear";
		std::string quadraticUniformName = prefix + "." + "quadratic";

		this->ApplyUniform(shader, ambientUniformName, this->GetAmbient());
		this->ApplyUniform(shader, diffuseUniformName, this->GetDiffuse());
		this->ApplyUniform(shader, specularUniformName, this->GetSpecular());
		this->ApplyUniform(shader, positionUniformName, this->GetPosition());
		this->ApplyUniform(shader, constantUniformName, this->GetConstant());
		this->ApplyUniform(shader, linearUniformName, this->GetLinear());
		this->ApplyUniform(shader, quadraticUniformName, this->GetQuadratic());
	}

	float GetConstant()
	{
		return this->constant;
	}

	float GetLinear()
	{
		return this->linear;
	}

	float GetQuadratic()
	{
		return this->quadratic;
	}

	glm::vec3 GetPosition()
	{
		return this->position;
	}

	void SetConstant(float constant)
	{
		this->constant = constant;
	}

	void SetLinear(float linear)
	{
		this->linear = linear;
	}

	void SetQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}

	void SetPosition(const glm::vec3& position)
	{
		this->position = position;
	}

private:
	float constant = 1.0f;
	float linear = 1.0f;
	float quadratic = 1.0f;

	glm::vec3 position;
};

class GLSpotLight : public GLPointLight
{
public:
	GLSpotLight()
	{

	}

	~GLSpotLight()
	{

	}

	void Apply(const GLSharedPtr<GLShader>& shader, int index)
	{
		if (!this->GetActive())
		{
			return;
		}

		std::string prefix = "spotLights[" + std::to_string(index) + "]";

		std::string ambientUniformName = prefix + "." + "ambient";
		std::string diffuseUniformName = prefix + "." + "diffuse";
		std::string specularUniformName = prefix + "." + "specular";
		std::string positionUniformName = prefix + "." + "position";
		std::string constantUniformName = prefix + "." + "constant";
		std::string linearUniformName = prefix + "." + "linear";
		std::string quadraticUniformName = prefix + "." + "quadratic";
		std::string cutOffUniformName = prefix + "." + "cutOff";
		std::string outerCutOffUniformName = prefix + "." + "outerCutOff";

		this->ApplyUniform(shader, ambientUniformName, this->GetAmbient());
		this->ApplyUniform(shader, diffuseUniformName, this->GetDiffuse());
		this->ApplyUniform(shader, specularUniformName, this->GetSpecular());
		this->ApplyUniform(shader, positionUniformName, this->GetPosition());
		this->ApplyUniform(shader, constantUniformName, this->GetConstant());
		this->ApplyUniform(shader, linearUniformName, this->GetLinear());
		this->ApplyUniform(shader, quadraticUniformName, this->GetQuadratic());
		this->ApplyUniform(shader, cutOffUniformName, this->GetCutOff());
		this->ApplyUniform(shader, outerCutOffUniformName, this->GetOuterCutOff());
	}

	float GetCutOff()
	{
		return this->cutOff;
	}

	float GetOuterCutOff()
	{
		return this->outerCutOff;
	}

	void SetCutOff(float cutOff)
	{
		this->cutOff = cutOff;
	}

	void SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = outerCutOff;
	}

private:
	float cutOff = 0.0f;
	float outerCutOff = 0.0f;
};