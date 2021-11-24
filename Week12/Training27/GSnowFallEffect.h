#pragma once

#include "../GL/GL.h"

class GSnow : public GUVSphere
{
private:
    static GLSharedPtr<GLMeshRenderer> sharedMeshRenderer;

    static GLSharedPtr<GLMeshRenderer> GetSharedMeshRenderer()
    {
        return sharedMeshRenderer;
    }

    static void SetSharedMeshRenderer(const GLSharedPtr<GLMeshRenderer>& meshRenderer)
    {
        sharedMeshRenderer = meshRenderer;
    }

public:
    GConstructor(GSnow)
        : GSuperClassInitializer(GUVSphere, 10, 5)
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        if (GetSharedMeshRenderer() == nullptr)
        {
            auto meshRenderer = this->GetMeshRenderer();

            this->GetMeshRenderer()->SetMaterial(GLGetPreDefinedMaterial("Turquoise"));
            SetSharedMeshRenderer(meshRenderer);
        }

        auto transform = this->GetTransform();
        transform->SetScale(0.05f, 0.05f, 0.05f);

        this->Reset();
    }

    void OnKeyDown(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyDown(key, x, y);

        if (key == "s")
        {
            this->SetVisible(!this->IsVisible());
        }
    }

    void OnKeyUp(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyUp(key, x, y);
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);

        auto transform = this->GetTransform();

        transform->Translate(0.0f, -fallSpeed * deltaTime, 0.0f);
        this->fallAmount += fallSpeed * deltaTime;

        if (transform->GetPosition().y <= 0.0f)
        {
            this->Reset();
        }
    }

    void Reset()
    {
        auto transform = this->GetTransform();

        transform->SetPosition(Rand3v(-2.0f, 2.0f, 1.0f, 3.0f, -2.0f, 2.0f));
        this->fallAmount = 0.0f;
    }

private:
    float fallSpeed = 1.0f;
    float fallAmount = 0.0f;
};

GLSharedPtr<GLMeshRenderer> GSnow::sharedMeshRenderer = nullptr;

class GSnowFallEffect : public GLGameObject
{
public:
    GConstructor(GSnowFallEffect)
        : GSuperClassInitializer(GLGameObject)
    {
        for (int i = 0; i < this->snowCount; ++i)
        {
            auto snow = GCreate(GSnow);
            this->AddChild(snow);

            snow->Initialize();
        }
    }

    void Initialize() override
    {
        GLGameObject::Initialize();
    }

    void OnKeyDown(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyDown(key, x, y);
    }

    void OnKeyUp(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyUp(key, x, y);
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);
    }

private:
    int snowCount = 100;
};