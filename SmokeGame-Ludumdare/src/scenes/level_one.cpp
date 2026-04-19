#pragma once

#include "level_one.h"


#include "../src/prefabs/level_prefab.h"
#include "../src/prefabs/grid_prefab.h"
#include "core/components/audioComponent.h"

void LevelOne::Build(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Node* gameplayMusic = builder.CreateNode("GameplayMusic");

	auto* music = gameplayMusic->AddComponent<Engine::AudioComponent>(rm.GetAudioClip("res/audio/gameplay.mp3"), true, true);

	Engine::AudioPlayParams params = music->GetParams();
	params.volume = 0.3f;
	music->SetParams(params);

	StartLevel(builder);

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;
}
