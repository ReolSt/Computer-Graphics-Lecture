#pragma once

#include "../GL/GL.h"

class GFractalTriangle : public GLGameObject
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
    GConstructor(GFractalTriangle)
        : GSuperClassInitializer(GLGameObject)
    {
       
    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        if (GetSharedMeshRenderer() == nullptr)
        {
            auto meshRenderer = GCreate(GTriangle)->GetMeshRenderer();

            meshRenderer->SetMaterial(GLGetPreDefinedMaterial("Gold"));
            SetSharedMeshRenderer(meshRenderer);
        }

        this->Reset(0);
    }

    void Reset(int subdivision)
    {
        if (this->levels[subdivision].size() == 0)
        {
            this->Setup(subdivision, subdivision, 0.0f, 0.0f, 1.0f);
        }

        this->ClearChildren();
        for (const auto& triangle : this->levels[subdivision])
        {
            this->AddChild(triangle);
        }
    }

    void Setup(int level, int subdivision, float x, float y, float size)
    {
        if (subdivision > 0)
        {
            Setup(level, subdivision - 1, x, y + size / 4.0f, size / 2.0f);
            Setup(level, subdivision - 1, x - size / 4.0f, y - size / 4.0f, size / 2.0f);
            Setup(level, subdivision - 1, x + size / 4.0f, y - size / 4.0f, size / 2.0f);
        }
        else
        {
            auto triangle = GCreate(GLGameObject);
            this->levels[level].push_back(triangle);

            triangle->SetMeshRenderer(this->GetSharedMeshRenderer());

            triangle->Initialize();
            auto transform = triangle->GetTransform();

            transform->SetLocalPosition(x, y, 0.0f);
            transform->SetLocalScale(size, size, 1.0f);
        }
    }

    void OnKeyDown(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyDown(key, x, y);

        if (key == "0")
        {
            this->Reset(0);
        }
        else if (key == "1")
        {
            this->Reset(1);
        }
        else if (key == "2")
        {
            this->Reset(2);
        }
        else if (key == "3")
        {
            this->Reset(3);
        }
        else if (key == "4")
        {
            this->Reset(4);
        }
        else if (key == "5")
        {
            this->Reset(5);
        }
        else if (key == "6")
        {
            this->Reset(6);
        }
        else if (key == "7")
        {
            this->Reset(7);
        }
    }

    void OnKeyUp(const std::string& key, int x, int y) override
    {
        GLGameObject::OnKeyUp(key, x, y);
    }

    void Update(float deltaTime) override
    {
        GLGameObject::Update(deltaTime);
    }

    std::array<std::vector<GLSharedPtr<GLGameObject>>, 8> levels;
};

GLSharedPtr<GLMeshRenderer> GFractalTriangle::sharedMeshRenderer = nullptr;

class GFractalPhyramid : public GLGameObject
{
public:
    GConstructor(GFractalPhyramid)
        : GSuperClassInitializer(GLGameObject)
    {

    }

    void Initialize() override
    {
        GLGameObject::Initialize();

        auto left = GCreate(GLGameObject);
        auto right = GCreate(GLGameObject);
        auto back = GCreate(GLGameObject);
        auto front = GCreate(GLGameObject);

        auto leftTriangle = GCreate(GFractalTriangle);
        auto rightTriangle = GCreate(GFractalTriangle);
        auto backTriangle = GCreate(GFractalTriangle);
        auto frontTriangle = GCreate(GFractalTriangle);

        left->AddChild(leftTriangle);
        right->AddChild(rightTriangle);
        back->AddChild(backTriangle);
        front->AddChild(frontTriangle);

        leftTriangle->GetTransform()->SetLocalPosition(0.0f, 0.5f, 0.0f);
        rightTriangle->GetTransform()->SetLocalPosition(0.0f, 0.5f, 0.0f);
        backTriangle->GetTransform()->SetLocalPosition(0.0f, 0.5f, 0.0f);
        frontTriangle->GetTransform()->SetLocalPosition(0.0f, 0.5f, 0.0f);

        leftTriangle->Initialize();
        rightTriangle->Initialize();
        backTriangle->Initialize();
        frontTriangle->Initialize();

        auto bottom = GCreate(GRectangle);

        this->AddChildren({ left, right, back, front, bottom });

        auto leftTransform = left->GetTransform();
        auto rightTransform = right->GetTransform();
        auto backTransform = back->GetTransform();
        auto frontTransform = front->GetTransform();
        auto bottomTransform = bottom->GetTransform();

        leftTransform->LocalPosition.x -= 0.5f;
        leftTransform->LocalPosition.y -= 0.5f;

        rightTransform->LocalPosition.x += 0.5f;
        rightTransform->LocalPosition.y -= 0.5f;

        backTransform->LocalPosition.z -= 0.5f;
        backTransform->LocalPosition.y -= 0.5f;

        frontTransform->LocalPosition.z += 0.5f;
        frontTransform->LocalPosition.y -= 0.5f;

        bottomTransform->LocalPosition.y -= 0.5f;

        leftTransform->SetEulerAngles(glm::radians(-30.0f), glm::radians(-90.0f), 0.0f);
        rightTransform->SetEulerAngles(glm::radians(-30.0f), glm::radians(90.0f), 0.0f);
        backTransform->SetEulerAngles(glm::radians(-30.0f), glm::radians(180.0f), 0.0f);
        frontTransform->SetEulerAngles(glm::radians(-30.0f), glm::radians(0.0f), 0.0f);
        bottomTransform->SetEulerAngles(glm::radians(90.0f), 0.0f, 0.0f);

        left->Initialize();
        right->Initialize();
        back->Initialize();
        front->Initialize();
        bottom->Initialize();

        bottom->GetMeshRenderer()->SetMaterial(GLGetPreDefinedMaterial("Gold"));
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
};