#include "brother_prefab.h"

#include "../src/core/components/followComponent.h"
#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/animatedSpriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/scriptComponent.h"

#include "scripts/brother_script.h"

void AddBrother(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

    Engine::Texture2D brother_sprite_sheet = rm.GetTexture("res/sprites/brother/sprite_sheet.png");
    Engine::Texture2D death_sprite_sheet = rm.GetTexture("res/sprites/brother/death_sprite_sheet.png");

	Engine::Node* brother = builder.CreateNode("Brother");

    brother->transform->SetPosition(pos);

    auto* spriteNode = builder.CreateChildNode(brother,"TextureNode");
    auto* deathSpriteNode = builder.CreateChildNode(brother,"DeathSprite");

    spriteNode->transform->SetScale(Engine::Vector2f(0.2f,0.2f));
    deathSpriteNode->transform->SetScale(Engine::Vector2f(0.2f,0.2f));

    auto* sprite = spriteNode->AddComponent<Engine::AnimatedSpriteComponent>(brother_sprite_sheet,Engine::Pivot::Center);
    auto* deathSprite = deathSpriteNode->AddComponent<Engine::AnimatedSpriteComponent>(death_sprite_sheet,Engine::Pivot::Center);

    sprite->AddAnimationGrid("Idle",0,2,2,670,1100,1.0f);
    sprite->AddAnimationGrid("Jump",0,0,8,670,1100,0.125f);
    sprite->AddAnimationGrid("Walk",0,0,8,670,1100,0.125f);
    sprite->AddAnimationGrid("Fall",0,1,3,576,1100,0.125f, false);

    deathSprite->AddAnimationGrid("Death", 0, 0, 12, 1300, 1100, 0.225f, false);
    brother->AddComponent<Engine::FollowComponent>(brother,Engine::FollowMode::Strict);
	brother->AddComponent<Engine::ScriptComponent>(new BrotherScript);

    //deathSprite->Play("Death");
    sprite->Play("Idle");

    brother->AddComponent<Engine::ColliderComponent>(Engine::RectangleShape(Engine::Vector2f(100.0f,250.0f)));
}