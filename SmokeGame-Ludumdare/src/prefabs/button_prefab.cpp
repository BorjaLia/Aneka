#include "button_prefab.h"
#include "scripts/button_script.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/audioComponent.h"
#include "../src/core/components/scriptComponent.h"
#include "../src/core/components/buttonComponent.h"
#include "../src/core/components/textComponent.h"

Engine::Node* AddButton(Engine::SceneBuilder& builder, Engine::Vector2f pos, std::string buttonText, std::string mainNodeName, Engine::Vector2f scale, Engine::Texture2D hoverTex, Engine::Texture2D normalTex,Engine::Pivot pivot, float rotation)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Texture2D buttonTex = normalTex;
	Engine::Font* font = rm.GetFont("res/fonts/ReemKufiFunRegular.ttf", 200);

	Engine::Node* button = builder.CreateNode(mainNodeName);

	button->transform->SetPosition(pos);

	button->AddComponent<Engine::SpriteComponent>(buttonTex, pivot, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	button->AddComponent<Engine::AudioComponent>(rm.GetAudioClip("res/audio/NoNoise.wav"));

	button->AddComponent<Engine::ButtonComponent>(Engine::RectangleShape(Engine::Vector2f(0.0f, 0.0f)), Engine::RenderLayer::UI);

	auto* textNode = builder.CreateChildNode(button, "ButtonText");
	auto* text = textNode->AddComponent<Engine::TextComponent>(font, buttonText, 48.0f, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);
	text->alignment = Engine::TextAlignment::Center;
	text->pivot = pivot;

	button->AddComponent<Engine::ScriptComponent>(new ButtonScript(normalTex, hoverTex, scale, rotation));

	return button;
}