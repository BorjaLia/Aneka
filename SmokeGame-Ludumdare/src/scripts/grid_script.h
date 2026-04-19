#pragma once

#include <memory>

#include "core/scripts/script.h"
#include "core/scenes/Scene.h"

class GridScript : public Engine::Script
{
private:
	Engine::Vector2f iter;
	Engine::Vector2f dist;
	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> body;

	void OnStart() override;

public:
	GridScript(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> body, Engine::Vector2f dist, Engine::Vector2f iter);
};

