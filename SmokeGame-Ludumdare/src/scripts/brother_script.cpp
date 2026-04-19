#include "brother_script.h"
#include "events/hit_player.h"

void BrotherScript::Idle()
{
	animation->SetFlipX(false);

	animation->Play("Idle");
	ENGINE_LOG("Brother is Idle");
	animation->speedMultiplier = 1.0f;
}

void BrotherScript::Walk()
{
	followComp->SetTarget(target);

	animation->SetFlipX(!(target->GetGlobalPosition().x >= owner->transform->GetGlobalPosition().x));

	this->moving = true;

	animation->Play("Walk");
	ENGINE_LOG("Brother is Walking");
	animation->speedMultiplier = 1.0f;
	//animation->speedMultiplier = (this->speed / this->baseSpeed);
}

void BrotherScript::Jump()
{
	animation->Play("Jump");
	ENGINE_LOG("Brother is Jumping");
	animation->speedMultiplier = 1.0f;
}

void BrotherScript::Crouch()
{
	animation->Play("Crouch");
	ENGINE_LOG("Brother is Crouching");
	animation->speedMultiplier = 1.0f;
}

void BrotherScript::Fall()
{
	animation->Play("Fall");
	ENGINE_LOG("Brother is Falling");
	animation->speedMultiplier = 1.0f;
}

void BrotherScript::Death()
{
	animation->SetActive(false);
	Engine::Node* deathSprite = owner->FindChild("DeathSprite");
	deathSprite->transform->SetPosition(owner->transform->GetPosition());
	animation = deathSprite->GetComponent<Engine::AnimatedSpriteComponent>();
	animation->Play("Death");
	ENGINE_LOG("Brother is Dead :(");
	animation->speedMultiplier = 1.0f;
	Engine::Application::Get().GetTimerManager().SetTimeout(0.3f, [this]()
		{
			Engine::Node* heaven = Engine::Application::Get().GetSceneBuilder().CreateChildNode(this->owner, "Heaven");
			heaven->transform->SetPosition(Engine::Vector2f(20.0f,100.0f));
			this->speed = 5.0f;
			this->owner->GetComponent<Engine::FollowComponent>()->SetTarget(heaven);
		});
}

void BrotherScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<MoveEvent>([this](MoveEvent& e)
		{
			ENGINE_LOG("Brother recieved event");
			DoAction(e.GetTarget(), e.GetMoveType());
			e.handled = true;
		});

	//listenerId = eventBus->Subscribe<HitPlayer>([this](Engine::Node* enemy, HitType hit)
	//	{
	//		ENGINE_LOG("ASD");
	//	});

	animation = owner->FindChild("TextureNode")->GetComponent<Engine::AnimatedSpriteComponent>();
	trs = owner->transform;

	followComp = owner->GetComponent<Engine::FollowComponent>();
	followComp->SetMode(Engine::FollowMode::Strict);
	followComp->SetLerpSpeed(speed);
}

void BrotherScript::OnUpdate(float)
{
	if (!moving) return;
	if ((target->GetGlobalPosition() - owner->transform->GetGlobalPosition()).MagnitudeSquared() <= 5.0f)
	{
		Idle();
		FinishMoveEvent finishMoveEvent(owner->transform->GetGlobalPosition());
		ENGINE_LOG("Brother publishesd finished move event");
		followComp->SetMode(Engine::FollowMode::Linear);
		moving = false;
		Engine::Application::Get().GetEventBus().Publish(finishMoveEvent);
	}
}

void BrotherScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(MoveEvent::GetStaticType(), listenerId);
	}
}

//void BrotherScript::Move(float delta)
//{
//	if (state == State::Walk)
//	{
//		trs->SetPosition(trs->GetPosition() + dir * (speed * delta));
//	}
//}

void BrotherScript::DoAction(Engine::Node* target, MoveType move)
{
	this->target = target;

	if (!target)
	{
		ENGINE_WARN("NO TARGET! - Brother Script");
	}

	switch (move)
	{
	case MoveType::Idle:
		Idle();
		break;
	case MoveType::Walk:
		Walk();
		break;
	case MoveType::Jump:
		Jump();
		break;
	case MoveType::Crouch:
		Crouch();
		break;
	case MoveType::Death:
		Death();

		break;
	default:
		break;
	}
}

//void BrotherScript::PlayAnim()
//{
//
//	if (!animation) return;
//	switch (state)
//	{
//	case BrotherScript::State::Idle:
//		break;
//	case BrotherScript::State::Walk:
//		animation->Play("Walk");
//		break;
//	case BrotherScript::State::Jump:
//		break;
//	case BrotherScript::State::Air:
//		break;
//	case BrotherScript::State::Crouch:
//		break;
//	default:
//		break;
//	}
//}