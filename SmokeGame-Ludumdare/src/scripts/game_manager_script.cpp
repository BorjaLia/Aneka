#include "game_manager_script.h"

#include "events/action_queue_event.h"
#include "smokes.h"

#include "scenes/main_menu_scene.h"

GameManagerScript::GameManagerScript(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody, Engine::Vector2f gridIter)
{
	this->gridBody = gridBody;
	this->gridIter = gridIter;
}

void GameManagerScript::GetSmokeButtons()
{
	Engine::Node* uiNode = owner->GetParent()->FindChild("UI");
	if (!uiNode)
	{
		ENGINE_LOG("NO UI");
		return;
	}
	Engine::Node* inventory = uiNode->FindChild("Inventory");
	if (!inventory)
	{
		ENGINE_LOG("NO INVENTORY");
		return;
	}

	yellowSmoke = inventory->FindChild("YellowDust")->GetComponent<Engine::ButtonComponent>();
	greenSmoke = inventory->FindChild("GreenDust")->GetComponent<Engine::ButtonComponent>();
	redSmoke = inventory->FindChild("RedDust")->GetComponent<Engine::ButtonComponent>();
	blueSmoke = inventory->FindChild("BlueDust")->GetComponent<Engine::ButtonComponent>();

	Engine::Node* controls = uiNode->FindChild("MovementInventory");
	if (!controls)
	{
		ENGINE_LOG("NO CONTROLS");
		return;
	}

	playButton = controls->FindChild("Play")->GetComponent<Engine::ButtonComponent>();
	resetButton = controls->FindChild("Reset")->GetComponent<Engine::ButtonComponent>();

	yellowSmoke->SetOnClick([this]()
		{
			AddQueueMove(SmokeType::Crouch);
		});
	greenSmoke->SetOnClick([this]()
		{
			AddQueueMove(SmokeType::Jump);
		});
	redSmoke->SetOnClick([this]()
		{
			AddQueueMove(SmokeType::Right);
		});
	blueSmoke->SetOnClick([this]()
		{
			AddQueueMove(SmokeType::Left);
		});

	playButton->SetOnClick([this]()
		{
			ENGINE_LOG("Play called");
			startActions = true;
			playButton->SetOnClick([this]()
				{
					ENGINE_LOG("Play called - running");
				});
		});
	resetButton->SetOnClick([this]()
		{
			ENGINE_LOG("Reset called");

			Engine::Application::Get().ReloadCurrentScene();
		});
}

void GameManagerScript::AddQueueMove(SmokeType type)
{
	if (moveQueue.size() >= 10)
	{
		ENGINE_LOG("queue full!");
		return;
	}

	moveQueue.push(type);

	switch (type)
	{
	case SmokeType::None:
		ENGINE_LOG("Pushing " << "None" << " queue event - Game Manager");
		break;
	case SmokeType::Left:
		ENGINE_LOG("Pushing " << "Left" << " queue event - Game Manager");
		break;
	case SmokeType::Right:
		ENGINE_LOG("Pushing " << "Right" << " queue event - Game Manager");
		break;
	case SmokeType::Jump:
		ENGINE_LOG("Pushing " << "Jump" << " queue event - Game Manager");
		break;
	case SmokeType::Crouch:
		ENGINE_LOG("Pushing " << "Crouch" << " queue event - Game Manager");
		break;
	default:
		break;
	}

	QueueChangeEvent addQueueEvent(moveQueue);
	eventBus->Publish(addQueueEvent);

}

void GameManagerScript::OnWin()
{
	ENGINE_LOG("Win registered");
	gameEnded = true;
	Engine::Application::Get().GetTimerManager().SetTimeout(5.0f, [this]()
		{
			//--------------------------------
			Engine::Application::Get().LoadScene<MainMenuScene>(); //CAMBIAR A PROXIMO NIVEL!!!
			//--------------------------------
		});
}
void GameManagerScript::OnLose()
{
	ENGINE_LOG("Loss registered");
	gameEnded = true;
	Engine::Application::Get().GetTimerManager().SetTimeout(5.0f, [this]()
		{
			Engine::Application::Get().ReloadCurrentScene();
		});
}

void GameManagerScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<FinishMoveEvent>([this](FinishMoveEvent& e)
		{
			ENGINE_LOG("Manager recieved finish move event");

			brotherPos = e.GetPos();
			e.handled = true;

			Engine::Application::Get().GetTimerManager().SetTimeout(3.0f, [this]()
				{
					pendingAction = true;
				});
		});

	GetSmokeButtons();

	if (!yellowSmoke || !greenSmoke || !redSmoke || !blueSmoke)
	{
		ENGINE_ERROR("Smoke buttons not found! - Game manager");
	}

	//Engine::Node* testNode = Engine::Application::Get().GetSceneBuilder().CreateNode();
	//testNode->transform->SetPosition(Engine::Vector2f(500.0f, 450.0f));

	MoveEvent moveEvent(gridBody[0][0], MoveType::Walk);
	eventBus->Publish(moveEvent);

	//moveQueue.push(SmokeType::Jump);
}

void GameManagerScript::OnUpdate(float)
{
	if (!startActions || gameEnded) return;

	if (moveQueue.empty())
	{
		OnLose();
		return;
	}

	if (pendingAction)
	{
		pendingAction = false;

		SmokeType type = moveQueue.front();
		moveQueue.pop();

		Engine::Node* gridNodeTowards;

		Engine::Vector2f closestCell = GetClosestNode(brotherPos);
		Engine::Vector2f nextCell = closestCell;
		switch (type)
		{
		case SmokeType::Left:
			nextCell.x--;
			gridNodeTowards = gridBody[closestCell.x - 1][closestCell.y];
			break;

		case SmokeType::Right:
			nextCell.x++;
			gridNodeTowards = gridBody[closestCell.x + 1][closestCell.y];
			break;

		case SmokeType::Jump:
			nextCell.y++;
			gridNodeTowards = gridBody[closestCell.x][closestCell.y + 1];
			break;

		default:
			break;
		}

		if (IterExists(nextCell))
		{
			gridNodeTowards = gridBody[nextCell.x][nextCell.y];
			ENGINE_LOG("[ITER EXISTS]: moving to: " << gridNodeTowards->transform->GetPosition());
			MoveEvent moveEvent(gridNodeTowards, MoveType::Walk);
			Engine::Application::Get().GetEventBus().Publish(moveEvent);
		}
	}
}

void GameManagerScript::ReceiveMove(SmokeType move)
{
	moveQueue.push(move);
}

void GameManagerScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(FinishMoveEvent::GetStaticType(), listenerId);
	}
}
bool GameManagerScript::IterExists(Engine::Vector2f iter)
{
	return (iter.x >= 0 && iter.x < gridIter.x &&
		iter.y >= 0 && iter.y < gridIter.y);
}

Engine::Vector2i GameManagerScript::GetClosestNode(Engine::Vector2f pos)
{
	Engine::Vector2i closest = Engine::Vector2i(0, 0);

	for (int i = 0; i < gridIter.y; i++)
	{
		for (int j = 0; j < gridIter.x; j++)
		{
			if ((pos - gridBody[i][j]->transform->GetGlobalPosition()).MagnitudeSquared() < (pos - gridBody[closest.x][closest.y]->transform->GetGlobalPosition()).MagnitudeSquared())
			{
				closest.x = i;
				closest.y = j;
			}
		}
	}
	return closest;
}