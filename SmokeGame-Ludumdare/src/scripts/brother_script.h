#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

#include "../src/core/components/animatedSpriteComponent.h"

class BrotherScript : public Engine::Script
{
	enum class STATE
	{
		IDLE,
		WALK,
		JUMP,
		AIR,
		CROUCH
	};

private:
	Engine::EventBus* eventBus;
	Engine::EventListenerID listenerId;

	float speed = 400.f;
	STATE state = STATE::WALK;
	Engine::Vector2f dir = Engine::Vector2f(0.f, 0.f);

	Engine::TransformComponent* trs;
	Engine::AnimatedSpriteComponent* animation;

	void Move(float delta);
	void PlayAnim();
public:
	void OnStart() override;
	void OnUpdate(float delta) override;
	void OnDestroy() override;
};

