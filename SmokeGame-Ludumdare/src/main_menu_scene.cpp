#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"

#include "background.h"

class MainMenuScene : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override
    {
        auto& app = Engine::Application::Get();
        auto& rm = *app.GetResourceManager();

        Engine::Font* font = rm.GetFont("res/fonts/ReemKufiFunRegular.ttf", 48);

        AddBackground(builder);

        /*Engine::Node* camNode = */builder.CreateNode("MenuCamera");

        {
            Engine::Node* node = builder.CreateNode("TitleText");
            node->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopCenter, Engine::Vector2f(0.0f, 150.0f));
            Engine::TextComponent* txt = node->AddComponent<Engine::TextComponent>(
                font, "SmokeGame", 72.0f,
                Engine::Color{ 255, 255, 255, 255 },
                Engine::RenderLayer::UI);
            txt->alignment = Engine::TextAlignment::Center;
            txt->pivot = Engine::Pivot::TopCenter;
        }
    }
};