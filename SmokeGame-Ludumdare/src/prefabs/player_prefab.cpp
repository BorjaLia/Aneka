#include "player_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/audioComponent.h"
#include "core/components/uiAnchorComponent.h"
#include "../src/core/components/animatedSpriteComponent.h"

void AddPlayer(Engine::SceneBuilder& builder, Engine::Vector2f pos)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Node* player = builder.CreateNode("Player");

    Engine::Texture2D idle_animation = rm.GetTexture("res/sprites/player/idle_player.png");

    player->transform->SetPosition(pos);

    Engine::Node* bonfire = builder.CreateChildNode(player, "Bonfire");

    Engine::Texture2D bonfireTex = rm.GetTexture("res/sprites/platform_bonfire.png");

    bonfire->AddComponent<Engine::SpriteComponent>(bonfireTex, Engine::Pivot::TopCenter, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::World);
    Engine::Vector2f bonfPos = bonfire->transform->GetPosition();
    bonfire->transform->SetPosition(Engine::Vector2f(static_cast<Engine::Vector2f>(bonfPos.x + 150.0f, bonfPos.y - 170.0f)));
    bonfire->transform->SetScale((Engine::Vector2f(1.4f, 1.4f)));

    auto* spriteNode = builder.CreateChildNode(player, "TextureNode");

    spriteNode->transform->SetScale(Engine::Vector2f(0.4f, 0.4f));

    auto* sprite = spriteNode->AddComponent<Engine::AnimatedSpriteComponent>(idle_animation, Engine::Pivot::Center);

    sprite->AddAnimationGrid("Idle", 0, 0, 3, 507, 1370, 0.75f);
    sprite->Play("Idle");
    //player->AddComponent<Engine::AudioComponent>(rm.GetAudioClip("res/audio/NoNoise.wav"),true, true);

}