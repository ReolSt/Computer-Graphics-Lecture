#pragma once

#include <array>

#include <gl/glm/glm.hpp>

#include "GLColor.h"
#include "GLPoint.h"

class GLTriangle
{
public:
	GLTriangle() { }

	GLTriangle(const GLPoint& v1, const GLPoint& v2, const GLPoint& v3) 
		: v1(v1), v2(v2), v3(v3) { }

	GLTriangle(const std::array<glm::vec3, 3>& positions, const std::array<GLColor, 3>& colors)
		: v1(positions[0], colors[0]),
		  v2(positions[1], colors[1]),
	      v3(positions[2], colors[2]) { }

	GLPoint v1;
	GLPoint v2;
	GLPoint v3;
};