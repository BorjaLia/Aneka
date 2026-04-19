#include "ui_inventory_script.h"

#include "events/action_queue_event.h"

UiPowdersScript::UiPowdersScript()
{
}

void UiPowdersScript::UpdateSprites()
{
	Engine::ResourceManager* rm = Engine::Application::Get().GetResourceManager();

	for (auto& child : owner->GetChildren())
	{
		Engine::Texture2D tex;

		if (smokes.empty()) return;
		SmokeType currentSmoke = smokes.front();
		smokes.pop();

		switch (currentSmoke)
		{
		case SmokeType::None:
			tex = rm->GetWhitePixel();
			break;
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
		default:
			break;
		}
		if (auto* sprite = child->GetComponent<Engine::SpriteComponent>())
		{
			sprite->SetTexture(tex);
		}
	}
}

void UiPowdersScript::UpdateCampfire()
{
	if (smokes.empty()) return;

	SmokeType currentSmoke = smokes.front();
	smokes.pop();

	switch (currentSmoke)
	{
	case SmokeType::None:
		break;
	case SmokeType::Left:
		break;
	case SmokeType::Right:
		break;
	case SmokeType::Jump:
		break;
	case SmokeType::Crouch:
		break;
	default:
		break;
	}

	Engine::Application::Get().GetTimerManager().SetTimeout(1.0f, [this]()
		{
			UpdateCampfire();
		});
}

void UiPowdersScript::OnStart()
{

	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<QueueChangeEvent>([this](QueueChangeEvent& e)
		{
			this->smokes = e.GetSmokeQueue();
			e.handled = true;
			UpdateSprites();
			if (e.GetDone())
			{

			}
		});
}

void UiPowdersScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(QueueChangeEvent::GetStaticType(), listenerId);
	}
}
