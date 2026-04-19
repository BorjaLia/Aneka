#include "props_setter.h"

PropsSetter::PropsSetter(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody)
{
	this->gridBody = gridBody;
}

void PropsSetter::OnStart()
{
	propsVec.push_back(owner->FindChild("Props")->FindChild("o1"));
	propsVec.push_back(owner->FindChild("Props")->FindChild("f1"));

	ENGINE_LOG("re");
	ENGINE_LOG(gridBody[0][1]->transform->GetGlobalPosition());
}

void PropsSetter::OnUpdate(float)
{
	if (firstFrame)
	{
		ENGINE_LOG("re");
		ENGINE_LOG(gridBody[0][0]->transform->GetGlobalPosition());
		propsVec[0]->transform->SetPosition(gridBody[5][0]->transform->GetGlobalPosition());
		propsVec[1]->transform->SetPosition(gridBody[5][0]->transform->GetGlobalPosition());

		firstFrame = false;
	}
}

void PropsSetter::OnDestroy()
{

}
