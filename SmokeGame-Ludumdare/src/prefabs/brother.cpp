#include "brother.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"

void AddBrother(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Texture2D playerTex = rm.GetTexture("res/sprites/Brother.png");

    Engine::Node* brother = builder.CreateNode("Brother");

    brother->transform->SetPosition(pos);

    brother->AddComponent<Engine::SpriteComponent>(playerTex);
    brother->AddComponent<Engine::SpriteComponent>(playerTex);
    brother->AddComponent<Engine::ColliderComponent>();
}