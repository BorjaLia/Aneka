#include "player.h"

#include "../src/core/components/spriteComponent.h"

void AddPlayer(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Texture2D playerTex = rm.GetTexture("res/sprites/Player.png");

    Engine::Node* player = builder.CreateNode("Player");

    player->transform->SetPosition(pos);

    player->AddComponent<Engine::SpriteComponent>(playerTex);
}