#pragma once

#include <vector>

#include <reactphysics3d/reactphysics3d.h>

#include "GLMemoryHelpers.h"
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
		this->Transform = GLCreate<GLTransform>(this);
		this->MeshRenderer = GLCreate<GLMeshRenderer>();

		this->SetParent(nullptr);
	}

	GLGameObject(const GLSharedPtr<GLTransform>& parent)
	{
		this->Transform = GLCreate<GLTransform>(this);
		this->MeshRenderer = GLCreate<GLMeshRenderer>();

		this->SetParent(parent);
	}
	
	virtual ~GLGameObject() { }

	virtual void Initialize()
	{
		this->bInitialized = true;
	}

	virtual void OnKeyDown(const std::string& key, int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnKeyDown(key, x, y);
		}
	}

	virtual void OnKeyUp(const std::string& key, int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnKeyUp(key, x, y);
		}
	}

	virtual void OnMouseDown(int button,int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnMouseDown(button, x, y);
		}
	}

	virtual void OnMouseUp(int button, int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnMouseUp(button, x, y);
		}
	}

	virtual void OnMouseWheel(int wheel, int direction, int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnMouseWheel(wheel, direction, x, y);
		}
	}

	virtual void OnMouseMove(int button, int x, int y)
	{
		for (auto& child : this->Children)
		{
			child->OnMouseMove(button, x, y);
		}
	}

	virtual void OnMouseLeave()
	{
		for (auto& child : this->Children)
		{
			child->OnMouseLeave();
		}
	}

	virtual void OnMouseEnter()
	{
		for (auto& child : this->Children)
		{
			child->OnMouseEnter();
		}
	}

	virtual void Update(GLfloat deltaTime)
	{
		for (auto& child : this->Children)
		{
			child->Update(deltaTime);
		}
	};

	void Render(const std::string& layer, const glm::mat4& cameraMatrix)
	{
		if (layer != this->Layer)
		{
			return;
		}

		if (this->Transform == nullptr)
		{
			return;
		}

		if (!this->bVisible)
		{
			return;
		}

		this->Transform->Update();

		for (auto& child : this->Children)
		{
			child->Render(layer, cameraMatrix);
		}

		if (this->MeshRenderer != nullptr)
		{
			this->MeshRenderer->Render(this->Transform->LocalToWorldMatrix, cameraMatrix);
		}
	}

	GLSharedPtr<GLTransform> GetParent()
	{
		return this->Transform->Parent;
	}

	void SetParent(const GLSharedPtr<GLTransform>& parent)
	{
		this->Transform->SetParent(parent);

		if (parent != nullptr)
		{
			this->Scene = parent->GameObject->Scene;
		}
	}

	void AddChild(const GLSharedPtr<GLGameObject>& child)
	{
		assert(child != nullptr);

		child->SetParent(this->Transform);

		this->Children.push_back(child);
	}

	void AddChildren(const std::initializer_list<GLSharedPtr<GLGameObject>>& children)
	{
		for (const auto& child : children)
		{
			this->AddChild(child);
		}
	}

	void RemoveChild(const GLSharedPtr<GLGameObject>& child)
	{
		assert(child != nullptr);

		child->SetParent(nullptr);

		auto position = std::find(this->Children.begin(), this->Children.end(), child);
		
		if (position != this->Children.end())
		{

			this->Children.erase(position);
		}
	}

	void RemoveChildren(const std::initializer_list<GLSharedPtr<GLGameObject>>& children)
	{
		for (const auto& child : children)
		{
			this->RemoveChild(child);
		}
	}

	void ClearChildren()
	{
		this->Children.clear();
	}
	
	std::string GetLayer()
	{
		return this->Layer;
	}

	void SetLayer(const std::string& layer)
	{
		this->Layer = layer;
	}

	void SetVisible(bool bVisible)
	{
		this->bVisible = bVisible;
	}

	bool IsVisible()
	{
		return this->bVisible;
	}

	GLSharedPtr<GLMeshRenderer> MeshRenderer = nullptr;
	GLSharedPtr<GLTransform> Transform = nullptr;

	GLSharedPtr<GLScene> Scene = nullptr;
	std::vector<GLSharedPtr<GLGameObject>> Children;

private:
	bool bVisible = true;
	std::string Layer = "Default";

	bool bInitialized = false;
};

#define GConstructor(CLASSNAME, ...) \
CLASSNAME(const GLSharedPtr<GLTransform>& parent, ## __VA_ARGS__)

#define GSuperClassInitializer(SUPERCLASSNAME, ...) \
SUPERCLASSNAME(parent, ## __VA_ARGS__)

#define GCreate(CLASSNAME, ...) \
GLCreate<CLASSNAME>(nullptr, ## __VA_ARGS__)

#define GCreateChild(CLASSNAME, ...) \
GLCreate<CLASSNAME>(this->Transform, ## __VA_ARGS__)

#define GCreateAndAddChild(CLASSNAME, ...) \
this->AddChild(GCreate(CLASSNAME, ## __VA_ARGS__)) \

#define GCreateChildFor(PARENTGAMEOBJECT, CLASSNAME, ...) \
GLCreate<CLASSNAME>(((PARENTGAMEOBJECT))->Transform, ## __VA_ARGS__)

#define GCreateAndAddChildFor(PARENTGAMEOBJECT, CLASSNAME, ...) \
((PARENTGAMEOBJECT))->AddChild(GCreateChildFor(PARENTGAMEOBJECT, CLASSNAME), ## __VA_ARGS__) \

#define GAddChild(CHILDGAMEOBJECT) \
this->AddChild(((CHILDGAMEOBJECT)))

#define GAddChildren(...) \
this->AddChildren(__VA_ARGS__)

#define GAddChildTo(PARENTGAMEOBJECT, CHILDGAMEOBJECT) \
((PARENTGAMEOBJECT))->AddChild(((CHILDGAMEOBJECT)))

#define GAddChildrenTo(PARENTGAMEOBJECT, ...) \
((PARENTGAMEOBJECT))->AddChildren(__VA_ARGS__)

