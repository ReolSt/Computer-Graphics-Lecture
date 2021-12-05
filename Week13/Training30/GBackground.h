#pragma once

#include "../GL/GL.h"

class GBackground : public GLGameObject
{
public:
    GConstructor(GBackground)
        : GSuperClassInitializer(GLGameObject) { }

    void Initialize() override
    {
        GLGameObject::Initialize();

        auto meshRenderer = this->GetMeshRenderer();
        auto material = meshRenderer->GetMaterial();

        auto mesh = GLMeshLoader::Load("resources/Rectangle.obj");
        auto texture = GLTextureLoader::Load("resources/Background.png");

        meshRenderer->SetMesh(mesh);

        material->SetDiffuseMap(texture);

        auto shader = GLCreate<GLBasicTextureShader>();
        material->SetShader(shader);

        this->GetTransform()->Rotate(glm::radians(90.0f), 0.0f, 0.0f);
    }
};