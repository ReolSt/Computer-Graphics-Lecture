#pragma once

#include <gl/glm/glm.hpp>

#include "GLCollision.h"

class GLCollider
{
public:
	GLCollider() 
		: center(0.0f, 0.0f, 0.0f) { }

	virtual ~GLCollider() { }

	glm::vec3 center;

	virtual void OnCollisionEnter(const GLCollision& collision) { };
	virtual void OnCollisionExit(const GLCollision& collision) { };
	virtual void OnCollisionStay(const GLCollision& collision) { };

};

class GLBoxCollider : public GLCollider
{
public:
	GLBoxCollider() 
		: GLCollider(),
          size(1.0f, 1.0f, 1.0f) { }

	glm::vec3 center;
	glm::vec3 size;
};

class GLSphereCollider : public GLCollider
{
public:
	GLSphereCollider()
		: GLCollider(),
		  radius(1.0f) { }

	glm::vec3 center;
	float radius;
};