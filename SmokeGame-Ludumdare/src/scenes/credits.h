#pragma once
#include "core/scenes/Scene.h"
#include "../src/prefabs/level_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/buttonComponent.h"

#include "prefabs/cursor_prefab.h"
#include "prefabs/button_prefab.h"
#include "scenes/main_menu_scene.h"

class Credits : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override;
};