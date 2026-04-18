#pragma once
#include "event.h"
#include "../../input/Iinput.h"

namespace Engine
{
    class MouseButtonPressedEvent : public EventBase<MouseButtonPressedEvent>
    {
    private:
        MouseButton button;

    public:
        MouseButtonPressedEvent(MouseButton btn) : button(btn) {}

        MouseButton GetButton() const { return button; }
        const char* GetName() const override { return "MouseButtonPressedEvent"; }
    };

    class MouseButtonReleasedEvent : public EventBase<MouseButtonReleasedEvent>
    {
    private:
        MouseButton button;

    public:
        MouseButtonReleasedEvent(MouseButton btn) : button(btn) {}

        MouseButton GetButton() const { return button; }
        const char* GetName() const override { return "MouseButtonReleasedEvent"; }
    };
}