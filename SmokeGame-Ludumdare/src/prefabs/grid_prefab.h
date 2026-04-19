#pragma once

#include "core/scenes/Scene.h"

std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> AddGrid(Engine::SceneBuilder& builder, Engine::Vector2f pos, Engine::Vector2f dist, Engine::Vector2f iter);


