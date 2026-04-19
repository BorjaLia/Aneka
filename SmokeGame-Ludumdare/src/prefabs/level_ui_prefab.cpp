#include "level_ui_prefab.h"

#include "core/application.h"

#include "core/components/spriteComponent.h"
#include "core/components/textComponent.h"
#include "core/components/uiAnchorComponent.h"
#include "core/components/buttonComponent.h"

#include "main_menu_scene.h"

#include "button.h"

void AddLevelUI(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Node* node = builder.CreateNode("UI");

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	node->transform->SetPosition(center);
	//Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/ui_overlay.png"), Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	Engine::Node* menuButton = AddButton(builder, Engine::Vector2f(), "     Go  Back", "MenuButton", Engine::Vector2f(0.125f, 0.125f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), Engine::Pivot::TopLeft, 5.0f);
	auto* anchor = menuButton->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopLeft);
	anchor->SetOffset(Engine::Vector2f(50.0f, 50.0f));

	menuButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			Engine::Application::Get().GetSceneManager().LoadScene(std::make_unique<MainMenuScene>());
		});

	Engine::Texture2D handbagTex = rm.GetTexture("res/sprites/Handbag.png");

	Engine::Node* inventoryNode = builder.CreateChildNode(node, "Inventory");
	auto* inventoryAnchor = inventoryNode->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopRight);
	inventoryAnchor->SetOffset(Engine::Vector2f(0.0f, 250.0f));

	auto* handbagSprite = inventoryNode->AddComponent<Engine::SpriteComponent>(handbagTex, Engine::Pivot::RightCenter, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	handbagSprite->SetTargetSize({ 316.5f, 520.0f });

	Engine::Node* yellowDust = AddButton(builder, Engine::Vector2f() , " ", "Inventory", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/YellowDust.png"), rm.GetTexture("res/sprites/YellowDust.png"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* yellowDustAnchot = yellowDust->AddComponent<Engine::UIAnchorComponent>();
	yellowDustAnchot->SetOffset(Engine::Vector2f(-145.0f, -60.0f));

	yellowDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("yellow dust selected");
		});

	Engine::Node* blueDust = AddButton(builder, Engine::Vector2f() , " ", "Inventory", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/BlueDust.png"), rm.GetTexture("res/sprites/BlueDust.png"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* blueDustAnchor = blueDust->AddComponent<Engine::UIAnchorComponent>();
	blueDustAnchor->SetOffset(Engine::Vector2f(-145.0f, 10.0f));

	blueDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("blue dust selected");
		});

	Engine::Node* redDust = AddButton(builder, Engine::Vector2f() , " ", "Inventory", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/RedDust.png"), rm.GetTexture("res/sprites/RedDust.png"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* redDustAnchor = redDust->AddComponent<Engine::UIAnchorComponent>();
	redDustAnchor->SetOffset(Engine::Vector2f(-150.0f, 85.0f));

	redDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("red dust selected");
		});

	Engine::Node* greenDust = AddButton(builder, Engine::Vector2f() , " ", "Inventory", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/GreenDust.png"), rm.GetTexture("res/sprites/GreenDust.png"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* greenDustAnchor = greenDust->AddComponent<Engine::UIAnchorComponent>();
	greenDustAnchor->SetOffset(Engine::Vector2f(-150.0f, 155.0f));

	greenDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("green dust selected");
		});

}