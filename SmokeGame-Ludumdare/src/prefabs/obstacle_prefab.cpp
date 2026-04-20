#include "obstacle_prefab.h"

#include <string>

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/scriptComponent.h"

#include "events/hit_player.h"
#include "scripts/obstacle_script.h"

Engine::Node* AddObstacle(Engine::Node* props, Engine::SceneBuilder& builder, std::string name, Engine::Texture2D tex, Engine::Vector2f pos, Engine::Vector2f size, bool hurt)
{
	//auto& app = Engine::Application::Get();
	//auto& rm = *app.GetResourceManager();

	Engine::Node* node = builder.CreateChildNode(props, name);

	node->AddComponent<Engine::ScriptComponent>(new ObstacleScript);

	node->transform->SetPosition(pos);
	Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(tex, Engine::Pivot::Center);

	sprite->SetTargetSize(size);

	node->AddComponent<Engine::TriggerAreaComponent>(Engine::RectangleShape{ {120.0f, 120.0f} }, Engine::Vector2f(0.0f), false);

	return node;
}