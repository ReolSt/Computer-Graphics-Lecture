#pragma once

#include <vector>

#include "GLShader.h"
#include "GLTransform.h"
#include "GLMesh.h"
#include "GLMeshRenderer.h"

class GLGameObject
{
public:
	GLGameObject()
	{
		this->transform = std::make_shared<GLTransform>(*this);
		this->mesh_renderer = std::make_shared<GLMeshRenderer>(this->transform);
	}

	GLGameObject(const std::shared_ptr<GLTransform>& parent)
	{
		this->transform = std::make_shared<GLTransform>(*this);
		this->mesh_renderer = std::make_shared<GLMeshRenderer>(this->transform);

		this->transform->parent = parent;
	}
	
	virtual ~GLGameObject() { }

	virtual void OnKeyDown(unsigned char key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyDown(key, x, y);
		}
	}

	virtual void OnKeyUp(unsigned char key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyUp(key, x, y);
		}
	}

	virtual void OnSpecial(int key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnSpecial(key, x, y);
		}
	}

	virtual void OnSpecialUp(int key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnSpecialUp(key, x, y);
		}
	}

	virtual void OnMouseDown(int button,int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseDown(button, x, y);
		}
	}

	virtual void OnMouseUp(int button, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseUp(button, x, y);
		}
	}

	virtual void OnMouseWheel(int wheel, int direction, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseWheel(wheel, direction, x, y);
		}
	}

	virtual void OnMouseMove(int button, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseMove(button, x, y);
		}
	}

	virtual void OnMouseLeave(int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseLeave(x, y);
		}
	}

	virtual void OnMouseEnter(int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMouseEnter(x, y);
		}
	}

	virtual void OnMotion(int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnMotion(x, y);
		}
	}

	virtual void OnPassiveMotion(int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnPassiveMotion(x, y);
		}
	}

	virtual void Update(GLfloat delta_time)
	{
		if (this->transform != nullptr)
		{
			this->transform->Update();
		}

		for (auto& child : this->children)
		{
			child->Update(delta_time);
		}
	};

	void Render()
	{
		if (this->transform == nullptr)
		{
			return;
		}

		if (!this->visible)
		{
			return;
		}

		for (auto& child : this->children)
		{
			child->Render();
		}

		if (this->mesh_renderer != nullptr)
		{
			this->mesh_renderer->Render();
		}
	}

	void SetParent(const std::shared_ptr<GLGameObject>& parent)
	{
		this->transform->parent = parent->transform;
	}

	void SetParent(const std::shared_ptr<GLTransform>& parent)
	{
		this->transform->parent = parent;
	}

	std::shared_ptr<GLMeshRenderer> mesh_renderer = nullptr;
	std::shared_ptr<GLTransform> transform = nullptr;

	std::vector<std::shared_ptr<GLGameObject>> children;

	bool visible = true;
};