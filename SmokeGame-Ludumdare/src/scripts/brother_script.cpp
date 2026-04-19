#include "brother_script.h"

void BrotherScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<MoveEvent>([this](MoveEvent& e)
		{
			//Move();
			DoAction(e.GetTarget(), e.GetMoveType());
			ENGINE_LOG("Brother recieved event");
		});

	animation = owner->FindChild("TextureNode")->GetComponent<Engine::AnimatedSpriteComponent>();
	trs = owner->transform;

	followComp = owner->GetComponent<Engine::FollowComponent>();
	followComp->SetMode(Engine::FollowMode::Linear);
	followComp->SetLerpSpeed(speed);
}

void BrotherScript::OnUpdate(float)
{
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
	if (!target)
	{
		ENGINE_WARN("NO TARGET! - Brother Script");
		return;
	}

	followComp->SetTarget(target);

	animation->SetFlipX((target->GetGlobalPosition().x >= owner->transform->GetGlobalPosition().x));

	switch (move)
	{
	case MoveType::Idle:
		animation->Play("Idle");
		animation->speedMultiplier = 1.0f;
		break;
	case MoveType::Walk:
		animation->Play("Walk");
		animation->speedMultiplier = 1.0f;
		//animation->speedMultiplier = (this->speed / this->baseSpeed);
		break;
	case MoveType::Jump:
		animation->Play("Jump");
		animation->speedMultiplier = 1.0f;
		break;
	case MoveType::Crouch:
		animation->Play("Crouch");
		animation->speedMultiplier = 1.0f;
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