#include "ui_inventory_script.h"

#include "events/action_queue_event.h"

#include "core/components/animatedSpriteComponent.h"


UiPowdersScript::UiPowdersScript()
{
}

void UiPowdersScript::UpdateSprites()
{
	Engine::ResourceManager* rm = Engine::Application::Get().GetResourceManager();

	for (auto& child : owner->GetChildren())
	{
		if (child->name == "Smoke") continue;

		Engine::Texture2D tex = rm->GetTexture("res/sprites/empty.png");

		if (!smokes.empty())
		{
			SmokeType currentSmoke = smokes.front();
			smokes.pop();

			switch (currentSmoke)
			{
			case SmokeType::Left:
				tex = rm->GetTexture("res/sprites/BlueDust.png");
				break;
			case SmokeType::Right:
				tex = rm->GetTexture("res/sprites/RedDust.png");
				break;
			case SmokeType::Jump:
				tex = rm->GetTexture("res/sprites/GreenDust.png");
				break;
			case SmokeType::Crouch:
				tex = rm->GetTexture("res/sprites/YellowDust.png");
				break;
			case SmokeType::None:
			default:
				break;
			}
		}

		if (auto* sprite = child->GetComponent<Engine::SpriteComponent>())
		{
			sprite->SetTexture(tex);
		}
	}
}

void UiPowdersScript::UpdateCampfire()
{
	float animTime = smokeAmount;
	float timePerSmoke = 3.0f / smokeAmount;

	Engine::AnimatedSpriteComponent* anim = owner->FindChild("Smoke")->GetComponent<Engine::AnimatedSpriteComponent>();
	anim->speedMultiplier = animTime;
	if (smokes.empty())
	{
		anim->texture = Engine::Application::Get().GetResourceManager()->GetTexture("res/sprites/empty.png");
		return;
	}
	SmokeType currentSmoke = smokes.front();
	smokes.pop();

	switch (currentSmoke)
	{
	case SmokeType::None:
		break;
	case SmokeType::Left:
		anim->Play("Blue");
		break;
	case SmokeType::Right:
		anim->Play("Red");
		break;
	case SmokeType::Jump:
		anim->Play("Green");
		break;
	case SmokeType::Crouch:
		anim->Play("Yellow");
		break;
	default:
		break;
	}

	Engine::Application::Get().GetTimerManager().SetTimeout(timePerSmoke, [this]()
		{
			UpdateCampfire();
		});
}

void UiPowdersScript::OnStart()
{

	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<QueueChangeEvent>([this](QueueChangeEvent& e)
		{
			if (e.GetDone())
			{
				this->smokes = e.GetSmokeQueue();
				smokeAmount = this->smokes.size();
				UpdateCampfire();
			}
			else
			{
				this->smokes = e.GetSmokeQueue();
				UpdateSprites();
			}
			e.handled = true;
		});
}

void UiPowdersScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(QueueChangeEvent::GetStaticType(), listenerId);
	}
}
