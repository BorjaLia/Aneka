#pragma once
#include "KeyCodes.h"
#include "../Core/Types.h"
#include <optional>

namespace Engine
{

    class IInput
    {
    public:
        virtual ~IInput() = default;

        // --- TECLADO ---
        virtual bool IsKeyDown(Key key) const = 0;
        virtual bool IsKeyPressed(Key key) const = 0;
        virtual bool IsKeyReleased(Key key) const = 0;

        // --- MOUSE ---
        virtual bool IsMouseButtonDown(MouseButton button) const = 0;
        virtual bool IsMouseButtonPressed(MouseButton button) const = 0;
        virtual bool IsMouseButtonReleased(MouseButton button) const = 0;

        virtual Vector2f GetMousePosition() const = 0;
        virtual std::optional<Vector2f> GetMouseDelta() const = 0;
        virtual float GetMouseWheel() = 0; // Para zoom o scroll
    };
}