#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLTransform.h"
#include "GLGameObject.h"

#undef near
#undef far

class GLScene;

class GLCamera : public GLGameObject
{
public:
	GLCamera(const std::shared_ptr<GLTransform>& parent,
		GLfloat window_width, GLfloat window_height,
		GLfloat fov = 90.0f, GLfloat near = 0.1f, GLfloat far = 100.0f)
		: GLGameObject(parent), window_width(window_width), window_height(window_height),
	      fov(fov), near(near), far(far) { }

	virtual ~GLCamera()
	{

	}

	glm::mat4 ViewMatrix()
	{
		glm::mat4 rotation_matrix = glm::toMat4(glm::inverse(this->transform->Rotation()));
		glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -this->transform->Position());

		return rotation_matrix * translation_matrix;
	}

	glm::mat4 ProjectionMatrix()
	{
		return glm::perspective(glm::radians(this->fov), this->window_width / this->window_height, near, far);
	}

	GLfloat fov;
	GLfloat near;
	GLfloat far;

	GLfloat window_width;
	GLfloat window_height;
};