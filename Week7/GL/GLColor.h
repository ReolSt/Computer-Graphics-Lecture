#pragma once

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include <random>
#include <array>

struct GLColor
{
public:
	GLclampf r;
	GLclampf g;
	GLclampf b;
	GLclampf a;

	GLColor()
		: r(0.0f), g(0.0f), b(0.0f), a(1.0f) { }

	GLColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		: r(r), g(g), b(b), a(a) { }

	GLColor(GLclampf r, GLclampf g, GLclampf b)
		: r(r), g(g), b(b), a(1.0f) { }

	GLColor(std::array<GLclampf, 3>& color)
		: r(color[0]), g(color[1]), b(color[2]), a(1.0f) { }

	GLColor(std::array<GLclampf, 4>& color)
		: r(color[0]), g(color[1]), b(color[2]), a(color[3]) { }

	GLColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		: r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) { }

	GLColor(GLubyte r, GLubyte g, GLubyte b)
		: r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(1.0f) { }

	GLColor(std::array<GLubyte, 3>& color)
		: r(color[0] / 255.0f), g(color[1] / 255.0f), b(color[2] / 255.0f), a(1.0f) { }

	GLColor(std::array<GLubyte, 4>& color)
		: r(color[0] / 255.0f), g(color[1] / 255.0f), b(color[2] / 255.0f), a(color[3] / 255.0f) { }

	void Set(const GLColor& color);
	void Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a);
	void Set(GLclampf r, GLclampf g, GLclampf b);
	void Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	void Set(GLubyte r, GLubyte g, GLubyte b);

	void RandR();
	void RandG();
	void RandB();
	void RandA();
	void Rand3f();
	void Rand4f();
private:
	GLfloat Randf();
};

void GLColor::Set(const GLColor& color)
{
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

void GLColor::Set(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void GLColor::Set(GLclampf r, GLclampf g, GLclampf b)
{
	this->Set(r, g, b, 1.0f);
}

void GLColor::Set(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	this->r = r / 255.0f;
	this->g = g / 255.0f;
	this->b = b / 255.0f;
	this->a = a / 255.0f;
}

void GLColor::Set(GLubyte r, GLubyte g, GLubyte b)
{
	this->Set(r, g, b, 255);
}

GLfloat GLColor::Randf()
{
	static std::default_random_engine engine((unsigned int)time(0));
	static std::uniform_real_distribution<GLfloat> distribution(0.0f, 1.0f);

	return distribution(engine);
}

void GLColor::RandR()
{
	this->r = Randf();
}

void GLColor::RandG()
{
	this->g = Randf();
}
void GLColor::RandB()
{
	this->b = Randf();
}

void GLColor::RandA()
{
	this->a = Randf();
}

void GLColor::Rand3f()
{
	this->r = Randf();
	this->g = Randf();
	this->b = Randf();
}

void GLColor::Rand4f()
{
	this->r = Randf();
	this->g = Randf();
	this->b = Randf();
	this->a = Randf();
}