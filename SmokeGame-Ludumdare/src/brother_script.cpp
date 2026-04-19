#include "brother_script.h"

void BrotherScript::OnStart()
{
	animation = owner->GetComponent<Engine::AnimatedSpriteComponent>();
	trs = owner->GetComponent<Engine::TransformComponent>();
}

void BrotherScript::OnUpdate(float delta)
{
	dir = Engine::Vector2f(1.f, 0.f);
	Move(delta);
	PlayAnim();
}

void BrotherScript::Move(float delta)
{
	if (dir.x != 0.f || dir.y != 0.f)
	{
		trs->SetPosition(trs->GetPosition() + dir * (speed * delta));
	}
}

void BrotherScript::PlayAnim()
{
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