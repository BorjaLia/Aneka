#include "level_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/audioListenerComponent.h"

#include "brother.h"
#include "player.h"

void StartLevel(Engine::SceneBuilder& builder)
{
    auto& app = Engine::Application::Get();
    //auto& rm = *app.GetResourceManager();

    Engine::Node* node = builder.CreateNode("MainView");

    /*Engine::CameraComponent* cam = */node->AddComponent<Engine::CameraComponent>(app.GetInput());

    Engine::Vector2f center = app.GetWindow()->GetSize();
    node->transform->SetPosition(center/2.0f);


    Engine::Node* floor = builder.CreateNode("Floor");

    floor->transform->SetPosition(center - Engine::Vector2f(0.0f,-100.0f));
    
    //floor->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/plant2.png"));

    //Add background

    AddBrother(builder,Engine::Vector2f(100.0f,500.0f));
    AddPlayer(builder,Engine::Vector2f(center .x - 250.0f,250.0f));
}