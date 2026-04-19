#pragma once

#include "core/scripts/script.h"
#include "core/scenes/Scene.h"
#include "brother_script.h"
#include "grid_script.h"
#include "../src/core/components/scriptComponent.h"

class GameManagerScript : public Engine::Script
{
private:
	//Engine::ScriptComponent* grid;
	
	void OnStart() override;
public:
	GameManagerScript();

};

