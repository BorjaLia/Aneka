#pragma once
#include "IInput.h"

namespace Engine
{

    class RaylibInput : public IInput
    {
    public:
        RaylibInput() = default;
        ~RaylibInput() override = default;

        // Implementación de Teclado
        bool IsKeyDown(Key key) const override;
        bool IsKeyPressed(Key key) const override;
        bool IsKeyReleased(Key key) const override;

        // Implementación de Mouse
        bool IsMouseButtonDown(MouseButton button) const override;
        bool IsMouseButtonPressed(MouseButton button) const override;
        bool IsMouseButtonReleased(MouseButton button) const override;

        Vector2f GetMousePosition() const override;
        std::optional<Vector2f> GetMouseDelta() const override; // [C++17]
        float GetMouseWheel() override;
    };

}