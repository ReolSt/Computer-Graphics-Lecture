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
#include "GLCamera.h"

class GLScene
{
public:
	GLScene(const std::string& name)
		: name(name),
		  background(1.0f, 1.0f, 1.0f)
	{
		this->root = std::make_shared<GLGameObject>();
		this->root->scene = std::shared_ptr<GLScene>(this);
	}

	virtual ~GLScene() { }

	void SetCamera(const std::shared_ptr<GLCamera>& camera)
	{
		assert(camera != nullptr);

		this->active_camera = camera;
	}

	std::shared_ptr<GLGameObject> root;
	std::shared_ptr<GLCamera> active_camera;

	std::string name;

	GLColor background;
};
