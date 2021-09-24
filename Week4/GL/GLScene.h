#pragma once

#include <string>
#include <vector>
#include <memory>
#include <thread>
#include <ctime>
#include <chrono>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "GLColor.h"
#include "GLGameObject.h"

class GLScene
{
public:
	GLScene(const std::string& name)
		: name(name),
		  background(1.0f, 1.0f, 1.0f)
	{
		root = std::make_shared<GLGameObject>();
	}

	virtual ~GLScene() { }

	std::shared_ptr<GLGameObject> root;
	std::string name;

	GLColor background;
};