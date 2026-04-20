#pragma once

#include "core/application.h"
#include "core/events/EventBus.h"

enum class HitType
{
	Death,
	Win
};

class HitPlayer : public Engine::EventBase<HitPlayer>
{
private:
	Engine::Node* enemy;
	HitType type;
public:
	HitPlayer(Engine::Node* enemy, HitType type);
	Engine::Node* GetEnemy();
	HitType GetHitType();

	const char* GetName() const override;
};
