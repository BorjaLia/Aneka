#include "background.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/scriptComponent.h"

#include "backgroundScript.h"

void AddBackground(Engine::SceneBuilder& builder, Engine::RenderLayer layer)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Texture2D backgroundTex = rm.GetTexture("res/sprites/background.png");
	Engine::Texture2D cloudTex = rm.GetTexture("res/sprites/clouds.png");
	Engine::Texture2D mountainNearTex = rm.GetTexture("res/sprites/loop_mountain_2.png");
	Engine::Texture2D mountainFarTex = rm.GetTexture("res/sprites/loop_mountain_1.png");

	Engine::Node* background = builder.CreateNode("Background");

	Engine::Node* backgroundFar = builder.CreateChildNode(background, "backgroundFar");
	Engine::Node* backgroundFar2 = builder.CreateChildNode(backgroundFar, "backgroundFar2");
	backgroundFar2->transform->SetPosition(Engine::Vector2i(backgroundTex.size.x, 0));

	Engine::Node* clouds = builder.CreateChildNode(background, "clouds");
	Engine::Node* clouds2 = builder.CreateChildNode(clouds, "clouds2");
	clouds2->transform->SetPosition(Engine::Vector2i(cloudTex.size.x, 0));

	Engine::Node* mountainNear = builder.CreateChildNode(background, "mountainNear");
	Engine::Node* mountainNear2 = builder.CreateChildNode(mountainNear, "mountainNear2");
	mountainNear2->transform->SetPosition(Engine::Vector2i(mountainNearTex.size.x, 0));

	Engine::Node* mountainFar = builder.CreateChildNode(background, "mountainFar");
	Engine::Node* mountainFar2 = builder.CreateChildNode(mountainFar, "mountainFar2");
	mountainFar2->transform->SetPosition(Engine::Vector2i(mountainFarTex.size.x, 0));

	background->transform->SetPosition(app.GetWindow()->GetSize() / 2.0f);

	background->AddComponent <Engine::ScriptComponent>(new BackgroundScript);

	backgroundFar->AddComponent <Engine::SpriteComponent>(backgroundTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	clouds->AddComponent <Engine::SpriteComponent>(cloudTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	mountainNear->AddComponent <Engine::SpriteComponent>(mountainNearTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	mountainFar->AddComponent <Engine::SpriteComponent>(mountainFarTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);

	backgroundFar2->AddComponent <Engine::SpriteComponent>(backgroundTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	clouds2->AddComponent <Engine::SpriteComponent>(cloudTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	mountainNear2->AddComponent <Engine::SpriteComponent>(mountainNearTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
	mountainFar2->AddComponent <Engine::SpriteComponent>(mountainFarTex, Engine::Pivot::Center, Engine::Color(255, 255, 255, 255), layer);
}
