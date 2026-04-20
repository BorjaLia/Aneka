#include "props_setter.h"

PropsSetter::PropsSetter(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody)
{
	this->gridBody = gridBody;
}

void PropsSetter::OnStart()
{
	propsVec.push_back(owner->GetParent()->FindChild("Props")->FindChild("f1"));
	propsVec.push_back(owner->GetParent()->FindChild("Props")->FindChild("f2"));

	propsVec.push_back(owner->GetParent()->FindChild("Props")->FindChild("o1"));
	propsVec.push_back(owner->GetParent()->FindChild("Props")->FindChild("o2"));
	propsVec.push_back(owner->GetParent()->FindChild("Props")->FindChild("o3"));

	//propsVec.push_back(owner->FindChild("Props")->FindChild("f3"));
	//propsVec.push_back(owner->FindChild("Props")->FindChild("f4"));

	ENGINE_LOG("re");
	ENGINE_LOG(gridBody[0][1]->transform->GetGlobalPosition());
}

void PropsSetter::OnUpdate(float)
{
	if (firstFrame)
	{
		propsVec[0]->transform->SetPosition(gridBody[2][0]->transform->GetGlobalPosition() + Engine::Vector2f(200, -500));
		propsVec[1]->transform->SetPosition(gridBody[3][0]->transform->GetGlobalPosition() + Engine::Vector2f(1030, -475));

		propsVec[2]->transform->SetPosition(gridBody[4][0]->transform->GetGlobalPosition() + Engine::Vector2f(0.f, -25));
		propsVec[3]->transform->SetPosition(gridBody[8][0]->transform->GetGlobalPosition() + Engine::Vector2f(0.f, -25));
		propsVec[4]->transform->SetPosition(gridBody[12][0]->transform->GetGlobalPosition() + Engine::Vector2f(0.f, -10));

		firstFrame = false;
	}
}

void PropsSetter::OnDestroy()
{

}
