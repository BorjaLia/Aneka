#include "obstacle_script.h"

#include <memory>

#include "events/hit_player.h"

void ObstacleScript::OnStart()
{
	collider = owner->GetComponent<Engine::TriggerAreaComponent>();
	self = owner->GetParent();
	eventBus = &Engine::Application::Get().GetEventBus();

	collider->ConnectTriggerEnter([this](Engine::Node* other)
		{
			if (other->name == "Brother")
			{
				HitType type;
				if (hurt)
				{
					type = HitType::Death;
				}
				else
				{
					type = HitType::Win;
				}
				HitPlayer hitPlayer(owner, type);

				eventBus->Publish(hitPlayer);
				owner->GetComponent<Engine::TriggerAreaComponent>()->SetActive(false);
				ENGINE_LOG("Hit: " << owner->name);
			}
		});
}

void ObstacleScript::OnUpdate(float)
{

}

void ObstacleScript::OnDestroy()
{

}


