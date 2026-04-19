#include "brother.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/animatedSpriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/scriptComponent.h"
#include "brother_script.h"

void AddBrother(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	const Engine::Texture2D walkingAnimText = rm.GetTexture("res/sprites/brotherSheet.png");

	Engine::Node* brother = builder.CreateNode("Brother");

	Engine::AnimatedSpriteComponent* animations = brother->AddComponent<Engine::AnimatedSpriteComponent>(
		walkingAnimText,
		Engine::Pivot::TopLeft,
		Engine::Color(255, 255, 255, 255),
		Engine::RenderLayer::World
	);
	
	animations->AddAnimationGrid("Walk", 0, 0, 8, 520, 819, 0.135f, true);
	//animations->AddAnimationGrid("Idle", 0, 0, 8, 682, 682, 0.135f, true);
	
	brother->AddComponent<Engine::ScriptComponent>(new BrotherScript);
	brother->transform->SetPosition(pos);
	brother->transform->SetScale(Engine::Vector2f(0.3f, 0.3f));

	//Engine::SpriteComponent* sprite = brother->AddComponent<Engine::SpriteComponent>
	//    (
	//        walkingAnimText,
	//        Engine::Pivot::TopLeft,
	//        Engine::Color(255,255,255,255),
	//        Engine::RenderLayer::World
	//    );
}