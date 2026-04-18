#pragma once
#include "../Component.h"
#include "../Types.h" // Donde definimos Shape y Color
#include "../Math.h"  // Donde están tus Vector2f

namespace Engine
{
    class ColliderComponent : public Component
    {
    private:
        Shape shape;
        Vector2f offset;
        Color debugColor;
        bool autoFitToSprite;

    public:
        // Constructor con valores por defecto (una caja roja centrada)
        ColliderComponent(
            const Shape& initialShape = RectangleShape{ {50.0f, 50.0f} },
            const Vector2f& offset = { 0.0f, 0.0f },
            bool autoFit = false,
            const Color& color = { 255, 0, 0, 255 }
        );

        ~ColliderComponent() override = default;

        void Start() override;
        // Sobrescribimos el Draw para mandar la figura a la cola de debug
        void Draw(IRenderer* renderer) override;

        // Getters y Setters rápidos
        Shape GetShape() const { return shape; }
        void SetShape(const Shape& newShape) { shape = newShape; }

        Vector2f GetOffset() const { return offset; }
        void SetOffset(const Vector2f& newOffset) { offset = newOffset; }

        void SetDebugColor(const Color& color) { debugColor = color; }
    };
}