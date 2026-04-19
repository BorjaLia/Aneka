#include "brother.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/animatedSpriteComponent.h"
#include "../src/core/components/colliderComponent.h"

void AddBrother(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    //Engine::Texture2D brotherTex = rm.GetTexture("res/sprites/brother/brother.png");
    Engine::Texture2D brother_sptite_sheet = rm.GetTexture("res/sprites/brother/walk_animation.png");

    Engine::Node* brother = builder.CreateNode("Brother");

    brother->transform->SetPosition(pos);

    auto* spriteNode = builder.CreateChildNode(brother,"TextureNode");

    spriteNode->transform->SetScale(Engine::Vector2f(0.2f,0.2f));

    //auto* sprite = brother->AddComponent<Engine::SpriteComponent>(brotherTex,Engine::Pivot::Center);
    auto* sprite = spriteNode->AddComponent<Engine::AnimatedSpriteComponent>(brother_sptite_sheet,Engine::Pivot::Center);

    //sprite->SetTargetSize(Engine::Vector2f(500.0f,825.0f));

    sprite->AddAnimationGrid("Walk",0,0,8,670,1100,0.15f);

    sprite->Play("Walk");

    brother->AddComponent<Engine::ColliderComponent>(Engine::RectangleShape(Engine::Vector2f(100.0f,250.0f)));
}