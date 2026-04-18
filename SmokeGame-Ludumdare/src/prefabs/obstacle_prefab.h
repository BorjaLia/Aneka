#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

#include <string>

void AddObstacle(Engine::SceneBuilder& builder, std::string name, Engine::Texture2D tex, Engine::Vector2f pos, Engine::Vector2f size, bool hurt);