#include "player_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/audioComponent.h"
#include "../src/core/components/animatedSpriteComponent.h"

void AddPlayer(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Node* player = builder.CreateNode("Player");

    Engine::Texture2D idle_animation = rm.GetTexture("res/sprites/player/idle_player.png");

    player->transform->SetPosition(pos);

    auto* spriteNode = builder.CreateChildNode(player, "TextureNode");

    spriteNode->transform->SetScale(Engine::Vector2f(0.4f, 0.4f));

    auto* sprite = spriteNode->AddComponent<Engine::AnimatedSpriteComponent>(idle_animation, Engine::Pivot::Center);

    sprite->AddAnimationGrid("Idle", 0, 0, 3, 507, 1370, 0.75f);
    sprite->Play("Idle");
    //player->AddComponent<Engine::AudioComponent>(rm.GetAudioClip("res/audio/NoNoise.wav"),true, true);
}