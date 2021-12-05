#pragma once
#pragma once

#include <vector>
#include <string>

#include "GLMemoryHelpers.h"

class GLGameObject;

class GLComponent
{
public:
	GLComponent(const GLSharedPtr<GLGameObject>& gameObject)
	{
		this->GameObject = gameObject;
	}

	virtual ~GLComponent() { }

	virtual void OnKeyDown(const std::string& key, int x, int y)
	{

	}

	virtual void OnKeyUp(const std::string& key, int x, int y)
	{

	}

	virtual void OnMouseDown(int button, int x, int y)
	{

	}

	virtual void OnMouseUp(int button, int x, int y)
	{

	}

	virtual void OnMouseWheel(int wheel, int direction, int x, int y)
	{

	}

	virtual void OnMouseMove(int button, int x, int y)
	{

	}

	virtual void OnMouseLeave()
	{

	}

	virtual void OnMouseEnter()
	{

	}

	virtual void Update(float deltaTime)
	{

	}

	GLSharedPtr<GLGameObject> GameObject = nullptr;
};