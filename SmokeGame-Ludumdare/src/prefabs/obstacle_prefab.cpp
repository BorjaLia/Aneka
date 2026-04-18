#include "obstacle_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"

#include <string>

void AddObstacle(Engine::SceneBuilder& builder,std::string name,Engine::Texture2D tex, Engine::Vector2f pos, Engine::Vector2f size, bool hurt)
{
    //auto& app = Engine::Application::Get();
    //auto& rm = *app.GetResourceManager();

    Engine::Node* node = builder.CreateNode(name);

    node->transform->SetPosition(pos);
    Engine::SpriteComponent* sprite =  node->AddComponent<Engine::SpriteComponent>(tex, Engine::Pivot::Center);

    sprite->SetTargetSize(size);

    if (hurt)
    {
        node->AddComponent<Engine::ColliderComponent>(Engine::RectangleShape{ {50.0f, 50.0f} }, Engine::Vector2f(0.0f),true);
    }
}