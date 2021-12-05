#pragma once

#include "../GL/GL.h"

class GTransparentCube : public GCube
{
public:
    GConstructor(GTransparentCube)
        : GSuperClassInitializer(GCube) { }

    void Initialize() override
    {
        GCube::Initialize();

        auto meshRenderer = this->GetMeshRenderer();
        auto material = meshRenderer->GetMaterial();

        meshRenderer->SetBlend(true);
        meshRenderer->SetCullFace(false);

        auto mesh = GLMeshLoader::Load("resources/Cube.obj");
        auto texture = GLTextureLoader::Load("resources/TranslucentBlue.png", GL_RGBA);

        material->SetDiffuseMap(texture);

        material->SetShader(GLCreate<GLBasicTextureMaterialShader>());
    }
private:

};