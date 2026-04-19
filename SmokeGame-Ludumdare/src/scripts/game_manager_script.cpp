#include "game_manager_script.h"

#include "core/time.h"

static int move = 1;

GameManagerScript::GameManagerScript(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody)

{
	this->gridBody = gridBody;
}

void GameManagerScript::GetSmokeButtons()
{
	Engine::Node* ui = owner->FindChild("UI");
	if (!ui) return;

	Engine::Node* inventory = ui->FindChild("Inventory");;
	if (!inventory) return;

	yellowSmoke = inventory->FindChild("YellowDust")->GetComponent<Engine::ButtonComponent>();
	greenSmoke = inventory->FindChild("GreenDust")->GetComponent<Engine::ButtonComponent>();
	redSmoke = inventory->FindChild("RedDust")->GetComponent<Engine::ButtonComponent>();
	blueSmoke = inventory->FindChild("BlueDust")->GetComponent<Engine::ButtonComponent>();
}

void GameManagerScript::OnStart()
{
	eventBus = &Engine::Application::Get().GetEventBus();

	listenerId = eventBus->Subscribe<FinishMoveEvent>([this](FinishMoveEvent& e)
		{
			e.handled = true;
			ENGINE_LOG("Manager recieved finish move event");

			Engine::Node* target = nullptr;

			switch (move)
			{
			case 1:
				target = gridBody[2][0];
				break;

			case 2:
				target = gridBody[4][0];
				break;
			case 3:
				target = gridBody[0][0];
				break;
			default:
				break;
			}

			if (!target)
			{
				ENGINE_LOG("Manager to publish move NO TARGET");
				return;
			}

			ENGINE_LOG("Manager to publish move " << std::to_string( move));

			MoveEvent moveEvent(target, MoveType::Walk);
			Engine::Application::Get().GetEventBus().Publish(moveEvent);
			
			move++;
		});

	GetSmokeButtons();

	if (!yellowSmoke || !greenSmoke || !redSmoke || !blueSmoke)
	{
		ENGINE_ERROR("Smoke buttons not found! - Game manager");
	}

	//Engine::Node* testNode = Engine::Application::Get().GetSceneBuilder().CreateNode();
	//testNode->transform->SetPosition(Engine::Vector2f(500.0f, 450.0f));

	MoveEvent moveEvent(gridBody[0][0], MoveType::Walk);
	Engine::Application::Get().GetEventBus().Publish(moveEvent);
}

void GameManagerScript::OnUpdate(float)
{
}

void GameManagerScript::OnDestroy()
{
	if (eventBus)
	{
		eventBus->Unsubscribe(FinishMoveEvent::GetStaticType(), listenerId);
	}
}

//
//enum class Smokes
//{
//
//};
//
//class BrotherMoveEvent : public Engine::EventBase<BrotherMoveEvent>
//{
//private:
//	int coinValue;
//public:
//	BrotherMoveEvent(int value = 1) : coinValue(value) {}
//	int GetValue() const { return coinValue; }
//
//	const char* GetName() const override { return "CoinCollectedEvent"; }
//};
//
//
//class CoinScript : public Engine::Script
//{
//private:
//	Engine::EventBus* eventBus;
//public:
//	CoinScript() = default;
//
//	void OnStart() override
//	{
//		auto* trigger = owner->GetComponent<Engine::TriggerAreaComponent>();
//		if (trigger)
//		{
//			trigger->ConnectTriggerEnter([this](Engine::Node* other)
//				{
//					if (other->name == "Player")
//					{
//						BrotherMoveEvent coinEvent(1);
//						Engine::Application::Get().GetEventBus().Publish(coinEvent);
//
//						owner->SetActive(false);
//					}
//				});
//		}
//	}
//};
//
//class ScoreUIListener : public Engine::Script
//{
//private:
//	Engine::EventBus* eventBus;
//	Engine::EventListenerID listenerId;
//
//public:
//	ScoreUIListener() = default;
//
//	void OnStart() override
//	{
//		eventBus = &Engine::Application::Get().GetEventBus();
//
//		listenerId = eventBus->Subscribe<BrotherMoveEvent>([this](BrotherMoveEvent& e)
//			{
//				currentCoins += e.GetValue();
//
//				ENGINE_LOG(currentCoins);
//			});
//	}
//
//	void OnDestroy() override
//	{
//		if (eventBus)
//		{
//			// Para desuscribirnos sí usamos el ID estático generado
//			eventBus->Unsubscribe(BrotherMoveEvent::GetStaticType(), listenerId);
//		}
//	}
//};