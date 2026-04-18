#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"

#include "../src/player.h"
#include "../src/prefabs/brother.h"

class LevelOne : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override
    {
        auto& app = Engine::Application::Get();
        //auto& rm = *app.GetResourceManager();

        Engine::Node* camera = builder.CreateNode("Camera");

        camera->AddComponent<Engine::CameraComponent>();

        Engine::Vector2i size = app.GetWindow()->GetSize() / 2;
        camera->transform->SetPosition(size);

        AddBrother(builder, {0.0f,0.0f});
    }
};