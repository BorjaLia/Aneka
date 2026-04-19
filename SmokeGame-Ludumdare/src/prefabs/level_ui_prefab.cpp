#include "level_ui_prefab.h"

#include "core/application.h"

#include "core/components/spriteComponent.h"
#include "core/components/textComponent.h"
#include "core/components/uiAnchorComponent.h"
#include "core/components/buttonComponent.h"
#include "core/components/scriptComponent.h"

#include "scripts/ui_inventory_script.h"

#include "scenes/main_menu_scene.h"

#include "button_prefab.h"

static void AssignSlots(Engine::SceneBuilder& builder, Engine::Node* node, int place)
{
	auto* rm = Engine::Application::Get().GetResourceManager();
	Engine::Node* slot = builder.CreateChildNode(node, std::to_string(place));

	slot->AddComponent<Engine::SpriteComponent>(rm->GetTexture(""), Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	slot->transform->SetPosition(Engine::Vector2f(place * 40.0f, 0.0f));
}

void AddLevelUI(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Node* node = builder.CreateNode("UI");

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	node->transform->SetPosition(center);
	//Engine::SpriteComponent* sprite = node->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/ui_overlay.png"), Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	Engine::Node* menuButton = AddButton(builder, Engine::Vector2f(), "   Go  Back", "MenuButton", Engine::Vector2f(0.125f, 0.125f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), rm.GetAudioClip("res/audio/button_click.wav"), Engine::Pivot::TopLeft, 5.0f);
	auto* anchor = menuButton->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopLeft);
	anchor->SetOffset(Engine::Vector2f(50.0f, 50.0f));

	menuButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			Engine::Application::Get().GetSceneManager().LoadScene(std::make_unique<MainMenuScene>());
		});

	Engine::Texture2D handbagTex = rm.GetTexture("res/sprites/Handbag.png");

	Engine::Node* inventoryNode = builder.CreateChildNode(node, "Inventory");
	auto* inventoryAnchor = inventoryNode->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::TopRight);
	inventoryAnchor->SetOffset(Engine::Vector2f(0.0f, 330.0f));
	inventoryNode->transform->SetScale(Engine::Vector2f(1.2f, 1.2f));

	auto* handbagSprite = inventoryNode->AddComponent<Engine::SpriteComponent>(handbagTex, Engine::Pivot::RightCenter, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	handbagSprite->SetTargetSize({ 316.5f, 520.0f });

	Engine::Node* yellowDust = AddButton(builder, Engine::Vector2f(), " ", "YellowDust", Engine::Vector2f(0.35f, 0.4f), rm.GetTexture("res/sprites/YellowDust.png"), rm.GetTexture("res/sprites/YellowDust.png"), rm.GetAudioClip("res/audio/dust_hover.wav"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* yellowDustAnchot = yellowDust->AddComponent<Engine::UIAnchorComponent>();
	yellowDustAnchot->SetOffset(Engine::Vector2f(-225.0, -120.0f));

	yellowDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("yellow dust selected");
		});

	Engine::Node* blueDust = AddButton(builder, Engine::Vector2f(), " ", "BlueDust", Engine::Vector2f(0.35f, 0.35f), rm.GetTexture("res/sprites/BlueDust.png"), rm.GetTexture("res/sprites/BlueDust.png"), rm.GetAudioClip("res/audio/dust_hover.wav"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* blueDustAnchor = blueDust->AddComponent<Engine::UIAnchorComponent>();
	blueDustAnchor->SetOffset(Engine::Vector2f(-115.0f, -125.0f));

	blueDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("blue dust selected");
		});

	Engine::Node* redDust = AddButton(builder, Engine::Vector2f(), " ", "RedDust", Engine::Vector2f(0.35f, 0.35f), rm.GetTexture("res/sprites/RedDust.png"), rm.GetTexture("res/sprites/RedDust.png"), rm.GetAudioClip("res/audio/dust_hover.wav"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* redDustAnchor = redDust->AddComponent<Engine::UIAnchorComponent>();
	redDustAnchor->SetOffset(Engine::Vector2f(-225.0, -35.0f));

	redDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("red dust selected");
		});

	Engine::Node* greenDust = AddButton(builder, Engine::Vector2f(), " ", "GreenDust", Engine::Vector2f(0.35f, 0.4f), rm.GetTexture("res/sprites/GreenDust.png"), rm.GetTexture("res/sprites/GreenDust.png"), rm.GetAudioClip("res/audio/dust_hover.wav"), Engine::Pivot::Center, 0.0f, inventoryNode);
	auto* greenDustAnchor = greenDust->AddComponent<Engine::UIAnchorComponent>();
	greenDustAnchor->SetOffset(Engine::Vector2f(-115.0f, -35.0f));

	greenDust->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("green dust selected");
		});

	Engine::Node* movementInventoryNode = builder.CreateChildNode(node, "MovementInventory");
	auto* movementInventoryAnchor = movementInventoryNode->AddComponent<Engine::UIAnchorComponent>(Engine::AnchorPreset::BottomLeft);
	auto* movementSprite = movementInventoryNode->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/movement_inventory.png"), Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);
	movementSprite->SetTargetSize({ 590.0f, 130.0f });
	movementInventoryAnchor->SetOffset(Engine::Vector2f(300.0f, -100.0f));

	Engine::Node* play = AddButton(builder, Engine::Vector2f(), " ", "Play", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/play.png"), rm.GetTexture("res/sprites/play.png"), rm.GetAudioClip("res/audio/button_click.wav"), Engine::Pivot::RightCenter, 5.0f, movementInventoryNode);
	auto* playAnchor = play->AddComponent<Engine::UIAnchorComponent>();
	playAnchor->SetOffset(Engine::Vector2f(360.0f, 0.0f));

	play->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("play selected");
		});

	Engine::Node* reset = AddButton(builder, Engine::Vector2f(), " ", "Reset", Engine::Vector2f(0.3f, 0.3f), rm.GetTexture("res/sprites/reset.png"), rm.GetTexture("res/sprites/reset.png"), rm.GetAudioClip("res/audio/button_click.wav"), Engine::Pivot::RightCenter, 5.0f, movementInventoryNode);
	auto* resetAnchor = reset->AddComponent<Engine::UIAnchorComponent>();
	resetAnchor->SetOffset(Engine::Vector2f(440.0f, 0.0f));

	reset->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("reset selected");
		});

	Engine::Node* powders = builder.CreateChildNode(movementInventoryNode, "Powders");

	powders->transform->SetPosition(Engine::Vector2f(0.0f, 0.0f));

	for (int i = 0; i < 10; i++)
	{
		AssignSlots(builder, powders, i);
	}
	powders->AddComponent<Engine::ScriptComponent>(new UiPowdersScript());
}