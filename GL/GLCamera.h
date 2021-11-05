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
		return this->ViewportPosition;
	}

	void SetViewportPosition(const glm::vec2& viewportPosition)
	{
		this->ViewportPosition = viewportPosition;
	}

	void SetViewportPosition(float x, float y)
	{
		this->ViewportPosition.x = x;
		this->ViewportPosition.y = y;
	}

	glm::vec2 GetViewportSize()
	{
		return this->ViewportSize;
	}

	void SetViewportSize(const glm::vec2& viewportSize)
	{
		this->ViewportSize = viewportSize;
	}

	void SetViewportSize(float x, float y)
	{
		this->ViewportSize.x = x;
		this->ViewportSize.y = y;
	}

	int GetOrder()
	{
		return this->Order;
	}

	void SetOrder(int order)
	{
		this->Order = order;
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
		glm::mat4 rotationMatrix = glm::toMat4(glm::inverse(this->Transform->Rotation));
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -this->Transform->Position);

		return rotationMatrix * translationMatrix;
	}

	virtual glm::mat4 GetProjectionMatrix() = 0;

	glm::mat4 GetCameraMatrix()
	{
		return this->GetProjectionMatrix() * this->GetViewMatrix();
	}

protected:
	glm::vec2 ViewportPosition = glm::vec2(0.0f, 0.0f);
	glm::vec2 ViewportSize = glm::vec2(1.0f, 1.0f);

	int Order = 0;
	bool bIsActive = false;
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
		return glm::perspective(glm::radians(this->Fov), this->ViewportSize.x / this->ViewportSize.y, this->Near, this->Far);
	}

	GLfloat Fov;
	GLfloat Near;
	GLfloat Far;
};