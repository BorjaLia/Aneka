#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"

#include "../src/prefabs/level_prefab.h"

class LevelOne : public Engine::IScene
{
public:
    void Build(Engine::SceneBuilder& builder) override
    {
        StartLevel(builder);
    }
};