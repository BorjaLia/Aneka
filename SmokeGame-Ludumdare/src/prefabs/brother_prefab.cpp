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

    Engine::Texture2D brother_sptite_sheet = rm.GetTexture("res/sprites/brother/sprite_sheet.png");

	Engine::Node* brother = builder.CreateNode("Brother");

    brother->transform->SetPosition(pos);

    auto* spriteNode = builder.CreateChildNode(brother,"TextureNode");

    spriteNode->transform->SetScale(Engine::Vector2f(0.2f,0.2f));

    auto* sprite = spriteNode->AddComponent<Engine::AnimatedSpriteComponent>(brother_sptite_sheet,Engine::Pivot::Center);

    sprite->AddAnimationGrid("Walk",0,0,8,670,1100,0.125f);
    sprite->AddAnimationGrid("Fall",0,1,3,576,1100,0.125f, false);
    sprite->AddAnimationGrid("Death",0,2,3,670,1100,0.125f, false);

    brother->AddComponent<Engine::FollowComponent>();
	brother->AddComponent<Engine::ScriptComponent>(new BrotherScript);

    //sprite->Play("Walk");

    brother->AddComponent<Engine::ColliderComponent>(Engine::RectangleShape(Engine::Vector2f(100.0f,250.0f)));
}