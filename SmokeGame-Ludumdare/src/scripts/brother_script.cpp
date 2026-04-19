#include "brother_script.h"

#include "events/move_event.h"

void BrotherScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<MoveEvent>([this](MoveEvent& e)
		{
			//Move();

			ENGINE_LOG("Brother recieved event");
		});

	animation = owner->FindChild("TextureNode")->GetComponent<Engine::AnimatedSpriteComponent>();
	trs = owner->transform;

	followComp = owner->GetComponent<Engine::FollowComponent>();
	followComp->SetMode(Engine::FollowMode::Lerp);
	followComp->SetLerpSpeed(speed);
}

void BrotherScript::OnUpdate(float)
{
	dir = Engine::Vector2f(1.f, 0.f);
	//Move(delta);
	PlayAnim();
}

void BrotherScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(MoveEvent::GetStaticType(), listenerId);
	}
}

void BrotherScript::Move(float delta)
{
	if (state == STATE::WALK)
	{
		trs->SetPosition(trs->GetPosition() + dir * (speed * delta));
	}
}

void BrotherScript::DoAction(Engine::Node* end, STATE state)
{
	this->state = state;
	if (this->state != STATE::CROUCH && this->state != STATE::WAIT)
	{
		followComp->SetTarget(end);
		followComp->SetStarted(true);
	}
	else
	{
		followComp->SetStarted(false);
	}
}

void BrotherScript::PlayAnim()
{
	if (dir.x != 0.f || dir.y != 0.f)
	{
		if (dir.y >= 0.f)
		{
			state = STATE::JUMP;
		}
		else if (dir.y < 0.f)
		{
			state = STATE::AIR;
		}
		else if (state != STATE::CROUCH)
		{
			state = STATE::WALK;
		}
	}

	if (!animation) return;
	switch (state)
	{
	case BrotherScript::STATE::IDLE:
		break;
	case BrotherScript::STATE::WALK:
		animation->Play("Walk");
		break;
	case BrotherScript::STATE::JUMP:
		break;
	case BrotherScript::STATE::AIR:
		break;
	case BrotherScript::STATE::CROUCH:
		break;
	default:
		break;
	}
}