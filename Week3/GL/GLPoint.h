#pragma once

#include <array>

#include <gl/glm/glm.hpp>

#include "GLColor.h"

class GLPoint
{
public:
	GLPoint() 
		: position(0.0f, 0.0f, 0.0f) { }

	GLPoint(const glm::vec3& position, const GLColor& color)
		: position(position), color(color) { }

	template <int N>
	GLPoint(const glm::vec3& position, const std::array<GLclampf, N>& color)
		: position(position), color(color) { }

	template <int N>
	GLPoint(const std::array<GLfloat, N>& position, const GLColor& color)
		: position(position), color(color) { }

	template <int N, int M>
	GLPoint(const std::array<GLfloat, N>& position, const std::array<GLclampf, M>& color)
		: position(position), color(color) { }

	glm::vec3 position;
	GLColor color;
};