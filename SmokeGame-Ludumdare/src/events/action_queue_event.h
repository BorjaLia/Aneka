#pragma once

#include "core/node.h"
#include "core/events/event.h"

#include "smokes.h"
#include <queue>

class QueueChangeEvent : public Engine::EventBase<QueueChangeEvent>
{
private:

	std::queue<SmokeType> smokeQueue;

public:
	QueueChangeEvent(std::queue<SmokeType> smokeQueue) : smokeQueue(smokeQueue) {}
	std::queue<SmokeType> GetSmokeQueue() const { return smokeQueue; }

	const char* GetName() const override { return "QueueChangeEvent"; }
};