#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

#include "../src/core/components/spriteComponent.h"

class BackgroundScript : public Engine::Script
{
private:

	const float parallax_speed_back = 0.0f;
	const float parallax_speed_mid = 40.0f;
	const float parallax_speed_mid_front = 140.0f;
	const float parallax_speed_front = 250.0f;

	Engine::Node* backgroundFar;
	Engine::Node* clouds;
	Engine::Node* mountainNear;
	Engine::Node* mountainFar;

public:

	void OnStart() override;
	void OnUpdate(float deltaTime) override;
};