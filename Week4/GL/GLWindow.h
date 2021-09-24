#pragma once

#include <string>

#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

class GLWindow
{
public:
	GLWindow(int x, int y, int w, int h, const std::string& title)
	{
		glutInitWindowPosition(x, y);
		glutInitWindowSize(w, h);

		this->position.x = x;
		this->position.y = y;

		this->size.x = w;
		this->size.y = h;

		this->id = glutCreateWindow(title.c_str());		
	}

	int Id()
	{
		return this->id;
	}

	glm::tvec2<int> Position()
	{
		return this->position;
	}

	glm::tvec2<int> Size()
	{
		return this->size;
	}

	void SetPosition(const glm::tvec2<int>& position)
	{
		this->position = position;

		glViewport(this->position.x, this->position.y, this->size.x, this->size.y);
	}

	void SetPosition(int x, int y)
	{
		this->position.x = x;
		this->position.y = y;

		glViewport(this->position.x, this->position.y, this->size.x, this->size.y);
	}

	void SetSize(const glm::tvec2<int>& position)
	{
		this->position = position;

		glViewport(this->position.x, this->position.y, this->size.x, this->size.y);
	}

	void SetSize(int w, int h)
	{
		this->size.x = w;
		this->size.y = h;

		glViewport(this->position.x, this->position.y, this->size.x, this->size.y);
	}
private:
	int id;

	glm::tvec2<int> position = glm::tvec2<int>(0, 0);
	glm::tvec2<int> size = glm::tvec2<int>(0, 0);
};