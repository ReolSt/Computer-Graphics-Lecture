#pragma once

#include "../GL/GL.h"

class GFloor : public GLGameObject
{
public:
	GConstructor(GFloor)
		: GSuperClassInitializer(GLGameObject)
	{

	}

	void Initialize() override
	{
		GLGameObject::Initialize();

		auto shape = GCreate(GRectangle);
		this->AddChild(shape);

		shape->Initialize();

		auto shapeTransform = shape->GetTransform();
		shapeTransform->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
		shapeTransform->SetLocalScale(5.0f, 5.0f, 5.0f);

		auto shapeMeshRenderer = shape->GetMeshRenderer();
		auto shapeMaterial = shapeMeshRenderer->GetMaterial();

		auto shapeTexture = GLTextureLoader::Load("Resources/brick.png");
		shapeMaterial->SetDiffuseMap(shapeTexture);
	}
};
