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

	float baseSpeed = 250.0f;
	float speed = baseSpeed;

	bool alive = true;

	bool moving = false;
	int height = 0;

	Engine::Vector2f deathPos;

	MoveType lastMove = MoveType::Idle;
	State state = State::Idle;

	Engine::TransformComponent* trs;
	Engine::AnimatedSpriteComponent* animation;
	Engine::FollowComponent* followComp;

	Engine::Node* target = nullptr;

	void Idle();
	void Walk();
	void Jump();
	void Crouch();
	void Fall();
	void Death();

	void DoAction(Engine::Node* target, MoveType move);
public:
	void OnStart() override;
	void OnUpdate(float delta) override;
	void OnDestroy() override;
};

