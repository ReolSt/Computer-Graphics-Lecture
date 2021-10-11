#pragma once

#include <vector>

#include "GLShader.h"
#include "GLTransform.h"
#include "GLMesh.h"
#include "GLMeshRenderer.h"

class GLScene;

class GLGameObject
{
public:
	GLGameObject()
	{
		this->transform = std::make_shared<GLTransform>(this);
		this->mesh_renderer = std::make_shared<GLMeshRenderer>(this->transform);
	}

	GLGameObject(const std::shared_ptr<GLTransform>& parent)
	{
		this->transform = std::make_shared<GLTransform>(this);
		this->mesh_renderer = std::make_shared<GLMeshRenderer>(this->transform);

		this->transform->parent = parent;

		if (this->transform->parent != nullptr)
		{
			this->scene = this->transform->parent->game_object->scene;
		}
	}
	
	virtual ~GLGameObject() { }

	virtual void OnKeyDown(const std::string& key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyDown(key, x, y);
		}
	}

	virtual void OnKeyUp(const std::string& key, int x, int y)
	{
		for (auto& child : this->children)
		{
			child->OnKeyUp(key, x, y);
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

	virtual void OnMouseLeave()
	{
		for (auto& child : this->children)
		{
			child->OnMouseLeave();
		}
	}

	virtual void OnMouseEnter()
	{
		for (auto& child : this->children)
		{
			child->OnMouseEnter();
		}
	}

	virtual void Update(GLfloat delta_time)
	{
		for (auto& child : this->children)
		{
			child->Update(delta_time);
		}
	};

	void Render(const glm::mat4& camera_matrix)
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
			child->Render(camera_matrix);
		}

		if (this->mesh_renderer != nullptr)
		{
			this->mesh_renderer->Render(camera_matrix * this->transform->localToWorldMatrix());
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

	std::shared_ptr<GLScene> scene = nullptr;

	std::vector<std::shared_ptr<GLGameObject>> children;

	bool visible = true;
};