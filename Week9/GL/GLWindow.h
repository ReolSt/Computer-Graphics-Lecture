#pragma once

#include <string>

#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLMemoryHelpers.h"

class GLWindow
{
public:
	GLWindow(int x, int y, int w, int h, const std::string& title)
	{
		glutInitWindowPosition(x, y);
		glutInitWindowSize(w, h);

		this->Position.x = x;
		this->Position.y = y;

		this->Size.x = w;
		this->Size.y = h;

		this->Title = title;
		this->Id = glutCreateWindow(this->Title.c_str());		
	}

	int GetId()
	{
		return this->Id;
	}

	glm::tvec2<int> GetPosition()
	{
		return this->Position;
	}

	glm::tvec2<int> GetSize()
	{
		return this->Size;
	}

	std::string GetTitle()
	{
		return this->Title;
	}

	void SetPosition(const glm::tvec2<int>& position)
	{
		this->Position = position;

		glViewport(this->Position.x, this->Position.y, this->Size.x, this->Size.y);
	}

	void SetPosition(int x, int y)
	{
		this->Position.x = x;
		this->Position.y = y;

		glViewport(this->Position.x, this->Position.y, this->Size.x, this->Size.y);
	}

	void SetSize(const glm::tvec2<int>& position)
	{
		this->Position = position;

		glViewport(this->Position.x, this->Position.y, this->Size.x, this->Size.y);
	}

	void SetSize(int w, int h)
	{
		this->Size.x = w;
		this->Size.y = h;

		glViewport(this->Position.x, this->Position.y, this->Size.x, this->Size.y);
	}
private:
	int Id;
	std::string Title;

	glm::tvec2<int> Position = glm::tvec2<int>(0, 0);
	glm::tvec2<int> Size = glm::tvec2<int>(0, 0);
};