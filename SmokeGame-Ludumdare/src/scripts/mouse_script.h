#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

class MouseScript : public Engine::Script
{
private:
	Engine::IInput* input;
	Engine::CameraComponent* camera;

public:
	
	MouseScript(Engine::CameraComponent* camera);

	void OnStart() override;
	void OnUpdate(float) override;
};