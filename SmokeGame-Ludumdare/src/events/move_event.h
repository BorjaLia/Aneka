#pragma once

#include "core/node.h"
#include "core/events/event.h"

enum class MoveType
{
	Idle,
	Walk,
	Jump,
	Crouch,
	Fall,
	Death
};

class MoveEvent : public Engine::EventBase<MoveEvent>
{
private:
	MoveType moveType;
	MoveType lastMove;
	Engine::Node* target;
public:
	MoveEvent(Engine::Node* target, MoveType moveType,MoveType lastMove = MoveType::Idle) : target(target), moveType(moveType),lastMove(lastMove) {}
	Engine::Node* GetTarget() const { return target; }
	MoveType GetMoveType() const { return moveType; }

	const char* GetName() const override { return "MoveEvent"; }
};

class FinishMoveEvent : public Engine::EventBase<FinishMoveEvent>
{
private:

	Engine::Vector2f pos;
	bool onAir;

public:
	FinishMoveEvent(Engine::Vector2f pos, bool onAir = false) :pos(pos),onAir(onAir) {}

	Engine::Vector2f GetPos() { return pos; }
	bool OnAir() { return onAir; }

	const char* GetName() const override { return "FinishMoveEvent"; }
};