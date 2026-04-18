#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"

#include "../src/prefabs/level_prefab.h"
#include "../src/prefabs/obstacle_prefab.h"


class LevelOne : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override
    {
        auto& app = Engine::Application::Get();
        auto& rm = *app.GetResourceManager();

        StartLevel(builder);

        Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

        std::cout << "center: " << center << '\n';

        AddObstacle(builder, "obsacle_one", rm.GetTexture("res/sprites/plant2.png"), center - Engine::Vector2f(50.0f, 10.0f), false);
    }
};