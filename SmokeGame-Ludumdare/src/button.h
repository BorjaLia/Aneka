#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"

#include "core/types.h"

void AddButton(Engine::SceneBuilder& builder, Engine::Vector2f pos, std::string buttonText, std::string mainNodeName, Engine::Vector2f scale, Engine::Texture2D hoverTex, Engine::Texture2D normalTex, float rotation);