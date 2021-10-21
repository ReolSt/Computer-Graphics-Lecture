#pragma once

#include <array>

#include <gl/glm/glm.hpp>

#include "GLColor.h"

class GLPoint
{
public:
	GLPoint() 
		: Position(0.0f, 0.0f, 0.0f) { }

	GLPoint(const glm::vec3& position, const GLColor& color)
		: Position(position), Color(color) { }

	template <int N>
	GLPoint(const glm::vec3& position, const std::array<GLclampf, N>& color)
		: Position(position), Color(color) { }

	template <int N>
	GLPoint(const std::array<GLfloat, N>& position, const GLColor& color)
		: Position(position), Color(color) { }

	template <int N, int M>
	GLPoint(const std::array<GLfloat, N>& position, const std::array<GLclampf, M>& color)
		: Position(position), Color(color) { }

	glm::vec3 Position;
	GLColor Color;
};