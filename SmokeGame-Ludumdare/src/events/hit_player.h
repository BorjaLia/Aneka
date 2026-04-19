#pragma once

#include "core/application.h"
#include "core/events/EventBus.h"

class HitPlayer : public Engine::EventBase<HitPlayer>
{
private:
	Engine::Node* enemy;

public:
	HitPlayer(Engine::Node* enemy);
	Engine::Node* GetEnemy();

	const char* GetName() const override;
};
