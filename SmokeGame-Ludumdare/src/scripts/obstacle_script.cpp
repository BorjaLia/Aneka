#include "obstacle_script.h"

#include <memory>

#include "events/hit_player.h"

void ObstacleScript::OnStart()
{
	collider = owner->GetComponent<Engine::TriggerAreaComponent>();
	self = owner->GetParent();
	eventBus = Engine::Application::Get().GetEventBus();

	collider->ConnectTriggerEnter([this](Engine::Node* other)
		{
			if (other->name == "Brother")
			{
				HitPlayer hitPlayer(owner);

				eventBus.Publish(hitPlayer);
				ENGINE_LOG("SUI");
			}
		});
}

void ObstacleScript::OnUpdate(float)
{

}

void ObstacleScript::OnDestroy()
{

}


