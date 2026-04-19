#pragma once

#include "core/application.h"
#include "core/scripts/script.h"

#include "core/components/spriteComponent.h"

#include "smokes.h"

#include <vector>
#include <queue>

class UiPowdersScript : public Engine::Script
{
private:

	Engine::EventBus* eventBus;
	Engine::EventListenerID listenerId;

	std::queue<SmokeType> smokes;

	float rotation;

	bool playedHoveredSound = false;

	void UpdateSprites();
	void UpdateCampfire();

public:

	UiPowdersScript();

	void OnStart() override;
	void OnDestroy() override;
};

