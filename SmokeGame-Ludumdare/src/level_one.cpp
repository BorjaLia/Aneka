#pragma once

#include "level_one.h"


#include "../src/prefabs/level_prefab.h"
#include "../src/prefabs/obstacle_prefab.h"

void LevelOne::Build(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();



	StartLevel(builder);

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	AddObstacle(builder, "obsacle_one", rm.GetTexture("res/sprites/plant2.png"), center - Engine::Vector2f(50.0f, 10.0f), Engine::Vector2f(200.0f, 200.0f), true);
}
