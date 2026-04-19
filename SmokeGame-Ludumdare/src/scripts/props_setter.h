#pragma once

#include "core/scripts/script.h"
#include "core/scenes/Scene.h"

class PropsSetter : public Engine::Script 
{
private:
	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBody;
	std::vector<Engine::Node*> propsVec;

	void OnStart() override;
	void OnUpdate(float) override;
	void OnDestroy() override;

	bool firstFrame = true;
public:
	PropsSetter(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> gridBodyc);
};

