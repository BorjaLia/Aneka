#include "obstacle_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"

#include <string>

void AddObstacle(Engine::SceneBuilder& builder,std::string name,Engine::Texture2D tex, Engine::Vector2f pos, bool hurt)
{
    //auto& app = Engine::Application::Get();
    //auto& rm = *app.GetResourceManager();

    Engine::Node* node = builder.CreateNode(name);

    node->transform->SetPosition(pos);
    Engine::SpriteComponent* sprite =  node->AddComponent<Engine::SpriteComponent>(tex, Engine::Pivot::Center);

    sprite->SetTargetSize({ 200.0f,200.0f });

    if (hurt)
    {
        node->AddComponent<Engine::ColliderComponent>();
    }
}