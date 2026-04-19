#pragma once

#include "core/node.h"
#include "core/events/event.h"

#include "smokes.h"
#include <queue>

class QueueChangeEvent : public Engine::EventBase<QueueChangeEvent>
{
private:

	std::queue<SmokeType> smokeQueue;
	bool isDone;

public:
	QueueChangeEvent(std::queue<SmokeType> smokeQueue, bool isDone = false) : smokeQueue(smokeQueue), isDone(isDone) {}
	std::queue<SmokeType> GetSmokeQueue() const { return smokeQueue; }
	bool GetDone() { return isDone; }

	const char* GetName() const override { return "QueueChangeEvent"; }
};