#pragma once
#include "../Component.h"
#include "../Types.h"
#include "../Math.h"
#include <functional> // Para nuestra señal

namespace Engine
{
    class Node; // Forward declaration

    class TriggerAreaComponent : public Component
    {
    public:
        // Nuestra "Señal": Un callback que avisa qué Nodo entró al área
        using TriggerSignal = std::function<void(Node* otherNode)>;

    private:
        Shape shape;
        Vector2f offset;
        Color debugColor;
        bool autoFitToSprite;

        TriggerSignal onTriggerEnter = nullptr; // El espacio en memoria para guardar la función

    public:
        // Constructor por defecto (amarillo semitransparente para diferenciarlo en debug)
        TriggerAreaComponent(
            const Shape& initialShape = RectangleShape{ {50.0f, 50.0f} },
            const Vector2f& offset = { 0.0f, 0.0f },
            bool autoFit = false,
            const Color& color = { 255, 255, 0, 255 }
        );

        ~TriggerAreaComponent() override = default;

        void Start() override;
        void Draw(IRenderer* renderer) override;

        Shape GetShape() const { return shape; }
        Vector2f GetOffset() const { return offset; }
        void SetDebugColor(const Color& color) { debugColor = color; }

        // La API de conexión (Igual a Godot)
        void ConnectTriggerEnter(TriggerSignal callback) { onTriggerEnter = callback; }

        void EmitTriggerEnter(Node* otherNode)
        {
            if (onTriggerEnter) onTriggerEnter(otherNode);
        }
    };
}