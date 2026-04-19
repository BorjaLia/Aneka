#include "level_ui_prefab.h"

#include "core/application.h"

#include "core/components/spriteComponent.h"
#include "core/components/textComponent.h"
#include "core/components/uiAnchorComponent.h"
#include "core/components/buttonComponent.h"

#include "button.h"

void AddLevelUI(Engine::SceneBuilder& builder)
{
    auto& app = Engine::Application::Get();
    auto& rm = *app.GetResourceManager();

    Engine::Node* node = builder.CreateNode("UI");

    Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

    node->transform->SetPosition(center);
    //Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/ui_overlay.png"), Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

    Engine::Node* menuButton = AddButton(builder,Engine::Vector2f(),"     Go  Back","MenuButton",Engine::Vector2f(0.125f,0.125f),rm.GetTexture("res/sprites/buttonHover.png"), rm.GetTexture("res/sprites/button.png"), Engine::Pivot::TopLeft, 5.0f);
    auto* anchor = menuButton->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopLeft);
    anchor->SetOffset(Engine::Vector2f(50.0f,50.0f));

    menuButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
        {
            ENGINE_LOG("MENU CALLED");
        });
}