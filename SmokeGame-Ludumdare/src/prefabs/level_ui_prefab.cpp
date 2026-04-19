#include "level_ui_prefab.h"

#include "core/application.h"

#include "core/components/spriteComponent.h"

//#include "button.h"

void AddLevelUI(Engine::SceneBuilder& builder)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Node* node = builder.CreateNode("UI");

    Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

    node->transform->SetPosition(center);
    Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/ui_overlay.png"), Engine::Pivot::Center);

    //AddButton();

}