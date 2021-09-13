#pragma once

#include <string>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "GLVector.h"

class GLWindow
{
public:
	GLWindow(int x, int y, int w, int h, const std::string& title)
	{
		glutInitWindowPosition(x, y);
		glutInitWindowSize(w, h);

		this->_position.x = x;
		this->_position.y = y;

		this->_size.x = w;
		this->_size.y = h;

		this->_id = glutCreateWindow(title.c_str());		
	}

	GLint Id()
	{
		return this->_id;
	}

	GLVector2<int> Position()
	{
		return this->_position;
	}

	GLVector2<int> Size()
	{
		return this->_size;
	}

	GLvoid SetPosition(const GLVector2<int>& position)
	{
		this->_position = position;

		glViewport(this->_position.x, this->_position.y, this->_size.x, this->_size.y);
	}

	GLvoid SetPosition(int x, int y)
	{
		this->_position.x = x;
		this->_position.y = y;

		glViewport(this->_position.x, this->_position.y, this->_size.x, this->_size.y);
	}

	GLvoid SetSize(const GLVector2<int>& position)
	{
		this->_position = position;

		glViewport(this->_position.x, this->_position.y, this->_size.x, this->_size.y);
	}

	GLvoid SetSize(int w, int h)
	{
		this->_size.x = w;
		this->_size.y = h;

		glViewport(this->_position.x, this->_position.y, this->_size.x, this->_size.y);
	}
private:
	GLint _id;

	GLVector2<int> _position = GLVector2<int>(0, 0);
	GLVector2<int> _size = GLVector2<int>(0, 0);
};