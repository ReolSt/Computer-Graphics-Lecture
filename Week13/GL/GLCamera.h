#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"
#include "GLTransform.h"
#include "GLGameObject.h"

#undef near
#undef far

class GLScene;

class GCamera : public GLGameObject
{
public:
	GConstructor(GCamera)
		: GSuperClassInitializer(GLGameObject)
	{
		this->bIsActive = true;
	}

	virtual ~GCamera() { }

	glm::vec2 GetViewportPosition()
	{
		return this->viewportPosition;
	}

	void SetViewportPosition(const glm::vec2& viewportPosition)
	{
		this->viewportPosition = viewportPosition;
	}

	void SetViewportPosition(float x, float y)
	{
		this->viewportPosition.x = x;
		this->viewportPosition.y = y;
	}

	glm::vec2 GetViewportSize()
	{
		return this->viewportSize;
	}

	void SetViewportSize(const glm::vec2& viewportSize)
	{
		this->viewportSize = viewportSize;
	}

	void SetViewportSize(float x, float y)
	{
		this->viewportSize.x = x;
		this->viewportSize.y = y;
	}

	int GetOrder()
	{
		return this->order;
	}

	void SetOrder(int order)
	{
		this->order = order;
	}

	bool IsActive()
	{
		return this->bIsActive;
	}

	void SetActive(bool bIsActive)
	{
		this->bIsActive = bIsActive;
	}

	virtual glm::mat4 GetViewMatrix()
	{
		auto transform = this->GetTransform();
		glm::mat4 rotationMatrix = glm::toMat4(glm::inverse(transform->Rotation));
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -transform->Position);

		return rotationMatrix * translationMatrix;
	}

	virtual glm::mat4 GetProjectionMatrix() = 0;

	void UpdateViewMatrix()
	{
		this->viewMatrix = this->GetViewMatrix();
	}

	void UpdateProjectionMatrix()
	{
		this->projectionMatrix = this->GetProjectionMatrix();
	}

	const glm::mat4& GetCachedViewMatrix()
	{
		return this->viewMatrix;
	}

	const glm::mat4& GetCachedProjectionMatrix()
	{
		return this->projectionMatrix;
	}

	void UpdateMatrices()
	{
		this->UpdateViewMatrix();
    	this->UpdateProjectionMatrix();
	}

protected:
	glm::vec2 viewportPosition = glm::vec2(0.0f, 0.0f);
	glm::vec2 viewportSize = glm::vec2(1.0f, 1.0f);

	int order = 0;
	bool bIsActive = false;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

class GOrthographicCamera : public GCamera
{
public:
	GConstructor(GOrthographicCamera,
		GLfloat left = -1.0f, GLfloat right= 1.0f, GLfloat bottom = -1.0f, GLfloat top = 1.0f,
		GLfloat near = 0.1f, GLfloat far = 100.0f)
		: GSuperClassInitializer(GCamera)
	{
		this->Near = near;
		this->Far = far;

		this->Left = left;
		this->Right = right;
		this->Bottom = bottom;
		this->Top = top;
	}

	~GOrthographicCamera() { }

	glm::mat4 GetProjectionMatrix() override
	{
		return glm::ortho(this->Left, this->Right, this->Bottom, this->Top, this->Near, this->Far);
	}

	GLfloat Near;
	GLfloat Far;

	GLfloat Left;
	GLfloat Right;
	GLfloat Bottom;
	GLfloat Top;
};

class GPerspectiveCamera : public GCamera
{
public:
	GConstructor(GPerspectiveCamera, GLfloat fov = 90.0f, GLfloat near = 0.1f, GLfloat far = 100.0f)
		: GSuperClassInitializer(GCamera)
	{
		this->Fov = fov;
		this->Near = near;
		this->Far = far;
	}

	~GPerspectiveCamera() { }

	glm::mat4 GetProjectionMatrix() override
	{
		return glm::perspective(glm::radians(this->Fov), this->viewportSize.x / this->viewportSize.y, this->Near, this->Far);
	}

	GLfloat Fov;
	GLfloat Near;
	GLfloat Far;
};