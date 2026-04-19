#pragma once

#include "core/node.h"
#include "core/events/event.h"

enum class MoveType
{
	Idle,
	Walk,
	Jump,
	Crouch,
	Death
};

class MoveEvent : public Engine::EventBase<MoveEvent>
{
private:
	MoveType moveType;
	Engine::Node* target;
public:
	MoveEvent(Engine::Node* target, MoveType moveType) : target(target), moveType(moveType) {}
	Engine::Node* GetTarget() const { return target; }
	MoveType GetMoveType() const { return moveType; }

	const char* GetName() const override { return "MoveEvent"; }
};

class FinishMoveEvent : public Engine::EventBase<FinishMoveEvent>
{
private:

	Engine::Vector2f pos;

public:
	FinishMoveEvent(Engine::Vector2f pos):pos(pos) {}

	Engine::Vector2f GetPos() { return pos; }

	const char* GetName() const override { return "FinishMoveEvent"; }
};