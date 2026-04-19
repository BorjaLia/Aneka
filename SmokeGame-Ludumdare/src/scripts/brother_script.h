#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

#include "../src/core/components/animatedSpriteComponent.h"
#include "../src/core/components/followComponent.h"

#include "events/move_event.h"

class BrotherScript : public Engine::Script
{
	enum class State
	{
		Idle,
		Wait,
		Walk,
		Jump,
		Air,
		Crouch,
		Death
	};

private:
	Engine::EventBus* eventBus;
	Engine::EventListenerID listenerId;

	float baseSpeed = 4.f;
	float speed = baseSpeed;

	State state = State::Walk;

	Engine::TransformComponent* trs;
	Engine::AnimatedSpriteComponent* animation;
	Engine::FollowComponent* followComp;

	//void Move(float delta);
	void DoAction(Engine::Node* target, MoveType move);
	//void PlayAnim();
public:
	void OnStart() override;
	void OnUpdate(float delta) override;
	void OnDestroy() override;
};

