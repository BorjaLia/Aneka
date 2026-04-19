#pragma once

#include "core/scripts/script.h"
#include "core/scenes/Scene.h"
#include "brother_script.h"
#include "grid_script.h"
#include "../src/core/components/scriptComponent.h"
#include "../src/core/components/buttonComponent.h"

#include "events/move_event.h"

#include <queue>

class GameManagerScript : public Engine::Script
{
private:
	//Engine::ScriptComponent* grid;
	
	Engine::EventBus* eventBus;
	Engine::EventListenerID listenerId;

	Engine::ButtonComponent* yellowSmoke;
	Engine::ButtonComponent* greenSmoke;
	Engine::ButtonComponent* redSmoke;
	Engine::ButtonComponent* blueSmoke;

	Engine::Node* brother;
	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody;

	float startTime = 0.0f;
	float actionInterval = 0.0f;

	void GetSmokeButtons();

	std::queue<MoveType> moveQueue;
	void OnStart() override;
	void OnUpdate(float) override;
	void OnDestroy() override;
public:
	GameManagerScript(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody);

};

