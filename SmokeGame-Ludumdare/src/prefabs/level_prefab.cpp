#include "level_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"

#include "brother.h"
#include "player.h"

void StartLevel(Engine::SceneBuilder& builder)
{
    auto& app = Engine::Application::Get();
    //auto& rm = *app.GetResourceManager();

    Engine::Node* camera = builder.CreateNode("Camera");

    /*Engine::CameraComponent* cam = */camera->AddComponent<Engine::CameraComponent>(app.GetInput());

    Engine::Vector2f center = app.GetWindow()->GetSize();
    camera->transform->SetPosition(center/2.0f);

    Engine::Node* floor = builder.CreateNode("Floor");

    floor->transform->SetPosition(center - Engine::Vector2f(0.0f,-100.0f));
    
    //floor->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/plant2.png"));

    //Add background

    AddBrother(builder,Engine::Vector2f(250.0f,250.0f));
    AddPlayer(builder,Engine::Vector2f(center .x - 250.0f,250.0f));
}