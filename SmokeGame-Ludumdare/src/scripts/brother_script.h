#pragma once

#include "core/application.h"
#include "core/scripts/script.h"


#include "../src/core/components/animatedSpriteComponent.h"
#include "../src/core/components/followComponent.h"

class BrotherScript : public Engine::Script
{
	enum class STATE
	{
		IDLE,
		WAIT,
		WALK,
		JUMP,
		AIR,
		CROUCH
	};

private:
	float speed = 400.f;
	STATE state = STATE::WALK;
	Engine::Vector2f dir = Engine::Vector2f(0.f, 0.f);

	Engine::TransformComponent* trs;
	Engine::AnimatedSpriteComponent* animation;
	Engine::FollowComponent* followComp;

	void Move(float delta);
	void DoAction(Engine::Node* end, STATE state);
	void PlayAnim();
public:
	void OnStart() override;
	void OnUpdate(float delta) override;
};

