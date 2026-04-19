#include "level_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/audioListenerComponent.h"

#include "background.h"

#include "../src/prefabs/grid_prefab.h"
#include "../src/core/components/scriptComponent.h"
#include "brother.h"
#include "player.h"
#include "game_manager_script.h"

void StartLevel(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	//auto& rm = *app.GetResourceManager();

	Engine::Node* gameManager = builder.CreateNode("GameManager");
	//gameManager->AddComponent<Engine::ScriptComponent<GameM>>

	Engine::Node* cam = builder.CreateNode("MainView");

	/*Engine::CameraComponent* cam = */cam->AddComponent<Engine::CameraComponent>(app.GetInput());

	Engine::Vector2f center = app.GetWindow()->GetSize();
	cam->transform->SetPosition(center / 2.0f);

	AddBackground(builder);

	Engine::Node* floor = builder.CreateNode("Floor");

	floor->transform->SetPosition(center - Engine::Vector2f(0.0f, -100.0f));

	//floor->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/plant2.png"));

	//Add background

	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> grid = AddGrid(builder, Engine::Vector2f(300.f, 300.f), Engine::Vector2f(100.f, 100.f), Engine::Vector2f(2, 2));
	AddBrother(builder, grid[0][0]->transform->GetPosition());
	Engine::Vector2f pos = grid[0][0]->transform->GetPosition();
	ENGINE_LOG(pos);
	AddPlayer(builder, Engine::Vector2f(center.x - 250.0f, 250.0f));
}