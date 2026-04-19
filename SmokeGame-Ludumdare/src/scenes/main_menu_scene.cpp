#pragma once

#include "main_menu_scene.h"
#include "level_one.h"

#include "core/application.h"
#include "core/scenes/SceneManager.h"
#include "core/types.h"

#include "core/components/uiAnchorComponent.h"
#include "core/components/textComponent.h"
#include "core/components/spriteComponent.h"
#include "core/components/buttonComponent.h"
#include "core/components/audioComponent.h"

#include "prefabs/background_prefab.h"
#include "prefabs/button_prefab.h"
#include "prefabs/cursor_prefab.h"

#include "core/debug.h"

void MainMenuScene::Build(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	//Engine::Font* font = rm.GetFont("res/fonts/ReemKufiFunRegular.ttf", 48);

	Engine::Node* mainMenuMusic = builder.CreateNode("MainMenuMusic");

	AddBackground(builder);

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	Engine::Node* camNode = builder.CreateNode("MenuCamera");
	camNode->transform->SetPosition(center);
	auto* cam = camNode->AddComponent<Engine::CameraComponent>();

	Engine::Texture2D titleTex = rm.GetTexture("res/sprites/aneka.png");

	Engine::Node* title = builder.CreateNode("TitleText");
	auto* sprite = title->AddComponent <Engine::SpriteComponent>(titleTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);
	sprite->SetTargetSize({ 750.0f, 600.0f });

	title->transform->SetPosition(center + Engine::Vector2f(0.0f, -230.0f));

	Engine::Node* playButton = AddButton(builder, center, "Play", "PlayButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), rm.GetAudioClip("res/audio/button_click.wav"),Engine::Pivot::Center, 15.0f, nullptr);

	playButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			Engine::Application::Get().LoadScene<LevelOne>();
		});

	Engine::Node* creditsButton = AddButton(builder, center + Engine::Vector2f(0.0f, 150.0f), "Credits", "CreditsButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), rm.GetAudioClip("res/audio/button_click.wav"), Engine::Pivot::Center,
		-15.0f, nullptr);
	creditsButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			ENGINE_LOG("Credits called");
		});
	
	Engine::Node* exitButton = AddButton(builder, center + Engine::Vector2f(0.0f, 300.0f), "Exit", "ExitButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), rm.GetAudioClip("res/audio/button_click.wav"),Engine::Pivot::Center,
		15.0f, nullptr);

	exitButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			Engine::Application::Get().Shutdown();
		});

	auto* music = mainMenuMusic->AddComponent<Engine::AudioComponent>(rm.GetAudioClip("res/audio/main_menu.mp3"), true, true);

	Engine::AudioPlayParams params = music->GetParams();
	params.volume = 0.3f;
	music->SetParams(params);

	AddCursor(builder, cam);
}