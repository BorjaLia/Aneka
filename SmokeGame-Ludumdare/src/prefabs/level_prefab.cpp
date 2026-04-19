#include "level_prefab.h"

#include "../src/core/components/spriteComponent.h"
#include "../src/core/components/colliderComponent.h"
#include "../src/core/components/audioListenerComponent.h"

#include "level_ui_prefab.h"
#include "background_prefab.h"

#include "../src/prefabs/grid_prefab.h"
#include "../src/core/components/scriptComponent.h"
#include "brother_prefab.h"
#include "player_prefab.h"
#include "scripts/game_manager_script.h"

#include "cursor_prefab.h"

void StartLevel(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	//auto& rm = *app.GetResourceManager();

    Engine::Node* camNode = builder.CreateNode("MainView");

    Engine::CameraComponent* cam = camNode->AddComponent<Engine::CameraComponent>(app.GetInput());

    Engine::Vector2f center = app.GetWindow()->GetSize();
    camNode->transform->SetPosition(center/2.0f);

    AddLevelUI(builder);

	AddBackground(builder);

	Engine::Node* floor = builder.CreateNode("Floor");

	floor->transform->SetPosition(center - Engine::Vector2f(0.0f, -100.0f));

	//floor->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/plant2.png"));

    AddGrid(builder, Engine::Vector2f(100.f,100.f), Engine::Vector2f(150.f,150.f), Engine::Vector2f(1,1));
    AddBrother(builder,Engine::Vector2f(250.0f,450.0f));
    AddPlayer(builder,Engine::Vector2f(center .x - 250.0f,250.0f));

    AddCursor(builder, cam);

    Engine::Node* gameManager = builder.CreateNode("GameManager");
    /*Engine::ScriptComponent* scriptComponent = */gameManager->AddComponent<Engine::ScriptComponent>(new GameManagerScript);
    //GameManagerScript* managerScript = scriptComponent->GetScript<GameManagerScript>();

}