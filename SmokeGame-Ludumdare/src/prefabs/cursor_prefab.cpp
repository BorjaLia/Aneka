#include "cursor_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/scriptComponent.h"
#include "scripts/mouse_script.h"

void AddCursor(Engine::SceneBuilder& builder, Engine::CameraComponent* camera)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

	Engine::Texture2D cursorTex = rm.GetTexture("res/sprites/Cursor.png");

	Engine::Node* cursor = builder.CreateNode("Cursor");

	Engine::SpriteComponent* sprite = cursor->AddComponent<Engine::SpriteComponent>(cursorTex, Engine::Pivot::TopLeft, Engine::Color(255, 255, 255, 255), Engine::RenderLayer::UI);

	sprite->SetTargetSize(Engine::Vector2f(40.0f,40.0f));
	sprite->SetFlipX(true);

	cursor->AddComponent<Engine::ScriptComponent>(new MouseScript(camera));
}
