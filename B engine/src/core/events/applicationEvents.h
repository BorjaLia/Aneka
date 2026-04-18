#pragma once
#include "event.h"
#include "../math.h"

namespace Engine
{
    // Window resize event containing new dimensions
    class WindowResizeEvent : public EventBase<WindowResizeEvent>
    {
    private:
        Vector2i size;

    public:
        WindowResizeEvent(const Vector2i& newSize) : size(newSize) {}
        WindowResizeEvent(int width, int height) : size(width, height) {}

        Vector2i GetSize() const { return size; }

        const char* GetName() const override { return "WindowResizeEvent"; }
    };

    // Triggered when the application window is closed
    class WindowCloseEvent : public EventBase<WindowCloseEvent>
    {
    public:
        WindowCloseEvent() = default;

        const char* GetName() const override { return "WindowCloseEvent"; }
    };
}