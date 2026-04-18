#pragma once
#include "../Component.h"
#include "../Events/Event.h"
#include "../Events/inputEvents.h"
#include "../types.h"
#include <functional>
#include <string>

namespace Engine
{
    class ButtonPressedEvent : public EventBase<ButtonPressedEvent>
    {
    private:
        std::string buttonName;

    public:
        ButtonPressedEvent(const std::string& name) : buttonName(name) {}

        std::string GetButtonName() const { return buttonName; }
        const char* GetName() const override { return "ButtonPressedEvent"; }
    };

    class ButtonComponent : public Component
    {
    private:
        RectangleShape shape;
        RenderLayer layer;

        bool autoFitToSprite;
        Vector2f offset;

        bool isHovered = false;
        bool isPressed = false;

        std::function<void()> onClickCallback;

        uint32_t mousePressedEventId = 0;
        uint32_t mouseReleasedEventId = 0;

        // Handlers de los eventos
        void OnMousePressed(MouseButtonPressedEvent& e);
        void OnMouseReleased(MouseButtonReleasedEvent& e);


    public:
        // Constructor actualizado: Ahora usa RectangleShape, offset y autoFit (por defecto true para mayor comodidad)
        ButtonComponent(const RectangleShape& initialShape = RectangleShape{ {0.0f, 0.0f} },
            RenderLayer layer = RenderLayer::UI,
            const Vector2f& offset = { 0.0f, 0.0f },
            bool autoFit = true
        );

        ~ButtonComponent() override;

        void Start() override;
        void Update(float deltaTime) override;
        void Draw(IRenderer* renderer) override;

        void SetOnClick(std::function<void()> callback) { onClickCallback = callback; }

        bool IsHovered() const { return isHovered; }
        bool IsPressed() const { return isPressed; }

        void SetOffset(Vector2f newoffset) { offset = newoffset; }

        void SetLayer(RenderLayer newLayer) { layer = newLayer; }
        RenderLayer GetLayer() const { return layer; }
    };
}