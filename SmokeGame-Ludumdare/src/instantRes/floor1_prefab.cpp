#include "../src/instantRes/floor1_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/scriptComponent.h"

Engine::Node* AddFloor1(Engine::Node* props, Engine::SceneBuilder& builder, std::string name, Engine::Texture2D tex, Engine::Vector2f pos, Engine::Vector2f size, bool hurt)
{
	Engine::Node* node = builder.CreateChildNode(props, name);

	node->transform->SetPosition(pos);
	Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(tex, Engine::Pivot::Center);

	sprite->SetTargetSize(size);

	node->AddComponent<Engine::TriggerAreaComponent>(Engine::RectangleShape{ {150.0f, 150.0f} }, Engine::Vector2f(0.0f), false);

	return node;
}
