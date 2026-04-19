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

		SmokeType currentSmoke = smokes.front();
		//smokes.pop();

		switch (currentSmoke)
		{
		case SmokeType::None:
			tex = rm->GetTexture("res/sprites/YellowDust.png");
			break;
		case SmokeType::Left:
			tex = rm->GetTexture("res/sprites/YellowDust.png");
			break;
		case SmokeType::Right:
			tex = rm->GetTexture("res/sprites/YellowDust.png");
			break;
		case SmokeType::Jump:
			tex = rm->GetTexture("res/sprites/YellowDust.png");
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

void UiPowdersScript::OnStart()
{

	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<QueueChangeEvent>([this](QueueChangeEvent& e)
		{
			this->smokes = e.GetSmokeQueue();
			e.handled = true;
			UpdateSprites();
		});
}

void UiPowdersScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(QueueChangeEvent::GetStaticType(), listenerId);
	}
}
