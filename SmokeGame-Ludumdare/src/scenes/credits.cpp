#include "credits.h"

void Credits::Build(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Vector2f center = app.GetWindow()->GetSize() / 2;

	Engine::Node* camNode = builder.CreateNode("CreditsCamera");
	camNode->transform->SetPosition(center);
	auto* cam = camNode->AddComponent<Engine::CameraComponent>();

	Engine::Texture2D creditsTex = rm.GetTexture("res/sprites/Credits.jpg");
	Engine::Node* credits = builder.CreateNode("Credits");

	credits->AddComponent<Engine::SpriteComponent>(creditsTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);
	credits->transform->SetPosition(center);

	Engine::Node* menuButton = AddButton(builder, center + Engine::Vector2f(600.0f, 450.0f), "Menu", "MenuButton", Engine::Vector2f(0.2f, 0.2f), rm.GetTexture("res/sprites/hoveredButton.png"), rm.GetTexture("res/sprites/button.png"), rm.GetAudioClip("res/audio/button_click.wav"), Engine::Pivot::Center,
		-15.0f, nullptr);

	menuButton->GetComponent<Engine::ButtonComponent>()->SetOnClick([]()
		{
			Engine::Application::Get().GetSceneManager().LoadScene(std::make_unique<MainMenuScene>());
		});

	AddCursor(builder, cam);

}
