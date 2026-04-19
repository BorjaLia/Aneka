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
#include "scripts/props_setter.h"
#include "../src/prefabs/obstacle_prefab.h"
#include "../src/instantRes/floor1_prefab.h"
#include "../src/instantRes/floor2_prefab.h"
#include "../src/instantRes/floor3_prefab.h"
#include "../src/instantRes/floor4_prefab.h"

void StartLevel(Engine::SceneBuilder& builder)
{
	auto& app = Engine::Application::Get();
	auto& rm = *app.GetResourceManager();

    Engine::Node* camNode = builder.CreateNode("MainView");

    Engine::CameraComponent* cam = camNode->AddComponent<Engine::CameraComponent>(app.GetInput());

    Engine::Vector2f center = app.GetWindow()->GetSize();
    camNode->transform->SetPosition(center/2.0f);

    AddLevelUI(builder);

	AddBackground(builder);

	Engine::Node* floor = builder.CreateNode("Floor");

	floor->transform->SetPosition(center - Engine::Vector2f(0.0f, -100.0f));

	floor->AddComponent<Engine::SpriteComponent>(rm.GetTexture("res/sprites/plant2.png"));

    Engine::Vector2f gridIter = Engine::Vector2f(15, 5);

    Engine::Vector2f scaler = Engine::Vector2f(125.f,125.f);

    std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody = AddGrid(builder, Engine::Vector2f(75.f, 350.f), scaler, gridIter);
   
    Engine::Node* props = builder.CreateNode("Props");

    AddFloor1(props, builder, "f1", rm.GetTexture("res/sprites/floor2.png"), Engine::Vector2f(0.f, 0.f), Engine::Vector2f(1200.f, 1000.f), true);
    AddFloor1(props, builder, "f2", rm.GetTexture("res/sprites/floor2.png"), Engine::Vector2f(0.f, 0.f), Engine::Vector2f(1200.f, 1000.f), true);

    AddBrother(builder);
    AddPlayer(builder,Engine::Vector2f(center .x - 250.0f,250.0f));

    AddCursor(builder, cam);

    Engine::Node* gameManager = builder.CreateNode("GameManager");


    gameManager->AddComponent<Engine::ScriptComponent>(new PropsSetter(gridBody));
    /*Engine::ScriptComponent* scriptComponent = */gameManager->AddComponent<Engine::ScriptComponent>(new GameManagerScript(gridBody, gridIter));
    //GameManagerScript* managerScript = scriptComponent->GetScript<GameManagerScript>();

   
    AddObstacle(props, builder, "o1", rm.GetTexture("res/sprites/cactus.png"), Engine::Vector2f(0.f, 0.f), scaler, true);

    //AddFloor2(props, builder, "f2", rm.GetTexture("res/sprites/floor2.png"), Engine::Vector2f(0.f, 0.f), Engine::Vector2f(132.f,125.f ), true);
    //AddFloor3(props, builder, "f3", rm.GetTexture("res/sprites/floor2.png"), Engine::Vector2f(0.f, 0.f), Engine::Vector2f(132.f,125.f ), true);
    //AddFloor4(props, builder, "f4", rm.GetTexture("res/sprites/floor2.png"), Engine::Vector2f(0.f, 0.f), Engine::Vector2f(132.f,125.f ), true);
}

