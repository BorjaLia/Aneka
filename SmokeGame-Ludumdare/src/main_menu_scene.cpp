#pragma once

#include "main_menu_scene.h"

#include "core/application.h"
#include "core/scenes/SceneManager.h"
#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"
#include "core/components/spriteComponent.h"
#include "core/components/buttonComponent.h"

#include "background.h"
#include "button.h"

void MainMenuScene::Build(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Font* font = rm.GetFont("res/fonts/ReemKufiFunRegular.ttf", 48);

	AddBackground(builder);

	/*Engine::Node* camNode = */builder.CreateNode("MenuCamera");

	Engine::Texture2D titleTex = rm.GetTexture("res/sprites/aneka.png");

	Engine::Node* title = builder.CreateNode("TitleText");
	auto* sprite = title->AddComponent <Engine::SpriteComponent>(titleTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);
	sprite->SetTargetSize({ 750.0f, 600.0f });
	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	title->transform->SetPosition(center + Engine::Vector2f(0.0f, -230.0f));

	AddButton(builder, center, "Play", "PlayButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), 15.0f);
	AddButton(builder, center + Engine::Vector2f(0.0f, 150.0f), "Credits", "CreditsButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), -15.0f);
	AddButton(builder, center + Engine::Vector2f(0.0f, 300.0f), "Exit", "ExitButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), 15.0f);
}