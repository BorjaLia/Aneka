#pragma once
#include "../Component.h"
#include "../Math.h"

namespace Engine
{

    class TransformComponent : public Component
    {
    private:
        Vector2f localPosition;
        float localRotation; // En grados
        Vector2f localScale;

        Matrix3x3 localMatrix;
        Matrix3x3 globalMatrix;

        bool isDirty; // La bandera de optimización
        void SetChildrenDirty();

    public:
        TransformComponent();
        ~TransformComponent() override = default;

        std::string ToString() const override;

        // Setters que automáticamente marcan el transform como "sucio"
        void SetPosition(const Vector2f& pos);
        void SetRotation(float rot);
        void SetScale(const Vector2f& scale);

        // Getters simples
        Vector2f GetPosition() const { return localPosition; }
        float GetRotation() const { return localRotation; }
        Vector2f GetScale() const { return localScale; }

        // Método principal para calcular la jerarquía
        void UpdateTransform();

        // Devuelve la matriz final calculada
        const Matrix3x3& GetGlobalMatrix();

        // Función de utilidad para obtener la posición global directamente de la matriz
        Vector2f GetGlobalPosition();
    };

}