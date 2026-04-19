#pragma once

#include "core/scenes/Scene.h"
#include "../src/prefabs/level_prefab.h"

class LevelOne : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override;
};