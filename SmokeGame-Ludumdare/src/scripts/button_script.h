#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/buttonComponent.h"
#include "../src/core/components/audioComponent.h"

class ButtonScript : public Engine::Script
{
private:
	Engine::ButtonComponent* button;
	Engine::SpriteComponent* sprite;

	Engine::Texture2D textureHover;
	Engine::Texture2D texture;

	Engine::Vector2f size;

	Engine::AudioClip audio;

	float rotation;

	bool playedHoveredSound = false;

public:

	ButtonScript(Engine::Texture2D texture, Engine::Vector2f size, float rotation, Engine::AudioClip audio);
	ButtonScript(Engine::Texture2D texture, Engine::Texture2D textureHover, Engine::Vector2f size, float rotation, Engine::AudioClip audio);

	void OnStart() override;
	void OnUpdate(float delta) override;
};

