#pragma once

#include "core/application.h"
#include "core/scenes/Scene.h"
#include "core/scenes/SceneManager.h"
#include "../src/core/components/audioComponent.h"

#include "core/types.h"

Engine::Node* AddButton(Engine::SceneBuilder& builder, Engine::Vector2f pos, std::string buttonText, std::string mainNodeName, Engine::Vector2f scale, Engine::Texture2D hoverTex, Engine::Texture2D normalTex, Engine::AudioClip audio, Engine::Pivot pivot, float rotation = 0.0f ,
	Engine::Node* parent = nullptr);