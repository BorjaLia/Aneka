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

    Engine::Vector2f gridIter = Engine::Vector2f(3, 3);
    std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody = AddGrid(builder, Engine::Vector2f(300.f, 300.f), Engine::Vector2f(150.f, 150.f), gridIter);
   
    AddBrother(builder,gridBody[0][0]->transform->GetGlobalPosition());
    AddPlayer(builder,Engine::Vector2f(center .x - 250.0f,250.0f));

    AddCursor(builder, cam);

    Engine::Node* gameManager = builder.CreateNode("GameManager");
    /*Engine::ScriptComponent* scriptComponent = */gameManager->AddComponent<Engine::ScriptComponent>(new GameManagerScript(gridBody, gridIter));
    //GameManagerScript* managerScript = scriptComponent->GetScript<GameManagerScript>();

}