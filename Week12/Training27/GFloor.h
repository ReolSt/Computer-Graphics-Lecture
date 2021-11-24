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
		auto shape = GCreate(GCube);
		this->AddChild(shape);

		shape->Initialize();

		shape->GetTransform()->SetScale(10.0f, 0.1f, 10.0f);
		RandMaterial(shape);
	}
};
