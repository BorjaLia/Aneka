#include "game_manager_script.h"

#include "core/time.h"

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
	GetSmokeButtons();

	if (!yellowSmoke || !greenSmoke || !redSmoke || !blueSmoke)
	{
		ENGINE_ERROR("Smoke button not found! - Game manager");
	}

	Engine::Node* testNode = Engine::Application::Get().GetSceneBuilder().CreateNode();
	testNode->transform->SetPosition(Engine::Vector2f(500.0f, 450.0f));

	MoveEvent moveEvent(testNode, MoveType::Jump);
	Engine::Application::Get().GetEventBus().Publish(moveEvent);
}

void GameManagerScript::OnUpdate(float)
{
	MoveEvent moveEvent();
	if (brother)
	{
		
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