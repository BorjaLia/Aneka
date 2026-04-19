#include "brother_script.h"

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

void BrotherScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<MoveEvent>([this](MoveEvent& e)
		{
			ENGINE_LOG("Brother recieved event");
			DoAction(e.GetTarget(), e.GetMoveType());
			e.handled = true;
		});

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
		FinishMoveEvent finishMoveEvent;
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