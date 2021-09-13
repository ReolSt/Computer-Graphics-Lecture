#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <random>

struct GLColor
{
public:
	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a;

	GLColor()
		: r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{
	}

	GLColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		: r(r), g(g), b(b), a(a)
	{
	}

	GLColor(GLclampf r, GLclampf g, GLclampf b)
		: r(r), g(g), b(b), a(1.0f)
	{
	}

	GLColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		: r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f)
	{
	}

	GLColor(GLubyte r, GLubyte g, GLubyte b)
		: r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(1.0f)
	{
	}

	GLvoid Set(const GLColor& color);
	GLvoid Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
	GLvoid Set(GLclampf r, GLclampf g, GLclampf b);
	GLvoid Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	GLvoid Set(GLubyte r, GLubyte g, GLubyte b);

	GLvoid RandR();
	GLvoid RandG();
	GLvoid RandB();
	GLvoid RandA();
	GLvoid Rand3f();
	GLvoid Rand4f();
private:
	GLfloat Randf();
};

GLvoid GLColor::Set(const GLColor& color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

GLvoid GLColor::Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

GLvoid GLColor::Set(GLclampf r, GLclampf g, GLclampf b)
{
	this->Set(r, g, b, 1.0f);
}

GLvoid GLColor::Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a / 255.0f;
}

GLvoid GLColor::Set(GLubyte r, GLubyte g, GLubyte b)
{
	this->Set(r, g, b, 255);
}

GLfloat GLColor::Randf()
{
	static std::default_random_engine engine(time(0));
	static std::uniform_real_distribution<GLfloat> distribution(0.0f, 1.0f);

	return distribution(engine);
}

GLvoid GLColor::RandR()
{
	this->r = Randf();
}

GLvoid GLColor::RandG()
{
	this->g = Randf();
}
GLvoid GLColor::RandB()
{
	this->b = Randf();
}

GLvoid GLColor::RandA()
{
	this->a = Randf();
}

GLvoid GLColor::Rand3f()
{
	this->r = Randf();
	this->g = Randf();
	this->b = Randf();
}

GLvoid GLColor::Rand4f()
{
	this->r = Randf();
	this->g = Randf();
	this->b = Randf();
	this->a = Randf();
}