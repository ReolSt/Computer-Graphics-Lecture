#pragma once

#include <random>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>

#include "GLColor.h"

template <typename T>
T Rand(T min, T max)
{
	static std::default_random_engine engine(time(NULL));

	std::uniform_int_distribution<T> distribution(min, max);
	return distribution(engine);
}

GLfloat Rand(GLfloat min, GLfloat max)
{
	static std::default_random_engine engine(time(NULL));

	std::uniform_real_distribution<GLfloat> distribution(min, max);
	return distribution(engine);
}

GLdouble Rand(GLdouble min, GLdouble max)
{
	static std::default_random_engine engine(time(NULL));

	std::uniform_real_distribution<GLdouble> distribution(min, max);
	return distribution(engine);
}

template <typename T>
glm::tvec2<T> Rand2v(T min_x, T max_x, T min_y, T max_y)
{
	return glm::tvec2<T>(Rand(min_x, max_x), Rand(min_y, max_y));
}

template <typename T>
glm::tvec3<T> Rand3v(T min_x, T max_x, T min_y, T max_y, T min_z, T max_z)
{
	return glm::tvec3<T>(Rand(min_x, max_x), Rand(min_y, max_y), Rand(min_z, max_z));
}

template <typename T>
glm::tvec4<T> Rand4v(T min_x, T max_x, T min_y, T max_y, T min_z, T max_z, T min_w, T max_w)
{
	return glm::tvec4<T>(Rand(min_x, max_x), Rand(min_y, max_y), Rand(min_z, max_z), Rand(min_w, max_w));
}


glm::vec2 ScreenToWorldPoint(int w, int h, int x, int y)
{
	x -= w / 2;
	y -= h / 2;

	return glm::vec2(x / (w / 2.0f), -y / (h / 2.0f));
}


glm::vec2 ScreenToWorldPoint(glm::tvec2<int> window_size, int x, int y)
{
	return ScreenToWorldPoint(window_size.x, window_size.y, x, y);
}

glm::vec2 ScreenToWorldPoint(glm::tvec2<int> window_size, glm::tvec2<int> mouse_position)
{
	return ScreenToWorldPoint(window_size.x, window_size.y, mouse_position.x, mouse_position.y);
}


glm::tvec2<int> WorldToScreenPoint(int w, int h, GLfloat x, GLfloat y)
{
	x += 1.0f;
	y += 1.0f;
	y = -y;

	return glm::tvec2<int>((int)(x * w), (int)(y * h));
}

glm::tvec2<int> WorldToScreenPoint(glm::tvec2<int> window_size, glm::vec2 position)
{
	return WorldToScreenPoint(window_size.x, window_size.y, position.x, position.y);
}
