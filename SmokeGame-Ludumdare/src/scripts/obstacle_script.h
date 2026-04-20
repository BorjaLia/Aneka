#pragma once

#include "core/application.h"
#include "core/scripts/script.h"
#include "../src/core/components/colliderComponent.h"

class ObstacleScript : public Engine::Script
{
private:
	Engine::TriggerAreaComponent* collider;
	Engine::EventBus* eventBus;
	Engine::EventListenerID eventId;
	Engine::Node* self;

public:
	void OnStart() override;
	void OnUpdate(float) override;
	void OnDestroy() override;
};

