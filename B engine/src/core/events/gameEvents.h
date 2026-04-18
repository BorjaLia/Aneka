#pragma once
#include "event.h"
#include "../math.h"

namespace Engine
{
    // Triggered when the player changes its position
    class PlayerMovedEvent : public EventBase<PlayerMovedEvent>
    {
    private:
        Vector2f newPosition;

    public:
        PlayerMovedEvent(const Vector2f& position) : newPosition(position) {}

        Vector2f GetPosition() const { return newPosition; }

        const char* GetName() const override { return "PlayerMovedEvent"; }
    };
}