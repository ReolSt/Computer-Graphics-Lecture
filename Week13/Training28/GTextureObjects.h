#pragma once

#include "../GL/GL.h"

class GTextureCube : public GLGameObject
{
public:
	GConstructor(GTextureCube)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto mesh = GLMeshLoader::Load("resources/Cube.obj");
		meshRenderer->SetMesh(mesh);

		auto texture = GLTextureLoader::Load("resources/Dice.png");
		material->SetDiffuseMap(texture);
	}
};

class GTexturePyramid : public GLGameObject
{
public:
	GConstructor(GTexturePyramid)
		: GSuperClassInitializer(GLGameObject) { }

	void Initialize() override
	{
		auto meshRenderer = this->GetMeshRenderer();
		auto material = meshRenderer->GetMaterial();

		auto pyramidMesh = GLMeshLoader::Load("resources/Pyramid.obj");
		meshRenderer->SetMesh(pyramidMesh);

		auto texture = GLTextureLoader::Load("resources/PyramidDice.png");
		material->SetDiffuseMap(texture);
	}
};