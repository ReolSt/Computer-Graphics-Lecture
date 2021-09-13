#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "GLColor.h"
#include "GLVector.h"

GLvoid GLClearColor(GLColor color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

GLvoid GLColor3f(GLColor color)
{
	glColor3f(color.r, color.g, color.b);
}

GLvoid GLColor4f(GLColor color)
{
	glColor4f(color.r, color.g, color.b, color.a);
}

GLvoid GLRectf(GLVector2<GLfloat> position, GLVector2<GLfloat> size)
{
	GLfloat left = position.x;
	GLfloat right = left + size.x;

	GLfloat top = position.y;
	GLfloat bottom = top - size.y;

	glRectf(left, top, right, bottom);
}