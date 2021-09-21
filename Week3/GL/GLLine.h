#pragma once

#include <array>

#include <gl/glm/glm.hpp>

#include "GLColor.h"
#include "GLPoint.h"

class GLLine
{
public:
	GLLine() { }

	GLLine(const GLPoint& v1, const GLPoint& v2)
	: v1(v1), v2(v2) { }

	GLLine(const std::array<glm::vec3, 2>& positions, const std::array<GLColor, 2>& colors)
		: v1(positions[0], colors[0]),
		  v2(positions[1], colors[1]) { }

	GLPoint v1;
	GLPoint v2;
};