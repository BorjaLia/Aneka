#include "TransformComponent.h"
#include "../Node.h"

// Constante para convertir grados a radianes
#define DEG2RAD (3.14159265f / 180.0f)

namespace Engine
{

    void TransformComponent::SetChildrenDirty()
    {
        if (owner == nullptr) return;

        for (auto& child : owner->GetChildren())
        {
            TransformComponent* childTransform = child->transform;


            if (!childTransform->isDirty)
            {
                childTransform->isDirty = true;
                childTransform->SetChildrenDirty();
            }
        }
    }

    TransformComponent::TransformComponent()
        : localPosition(0.0f, 0.0f), localRotation(0.0f), localScale(1.0f, 1.0f), isDirty(true)
    {
    }

    std::string TransformComponent::ToString() const
    {
        std::stringstream ss;
        ss << "TransformComponent [Pos: " << GetPosition();

        ss << " | Rotation: " << GetRotation();
        ss << " | Scale: " << GetScale();

        ss << "]";
        return ss.str();
    }

    void TransformComponent::SetPosition(const Vector2f& pos)
    {
        // Pequeña optimización: si nos mandan la misma posición, no hacemos nada
        if (localPosition.x == pos.x && localPosition.y == pos.y) return;

        localPosition = pos;
        if (!isDirty)
        {
            isDirty = true;
            SetChildrenDirty(); // Avisamos hacia abajo
        }
    }

    void TransformComponent::SetRotation(float rot)
    {
        if (localRotation == rot) return;

        localRotation = rot;
        if (!isDirty)
        {
            isDirty = true;
            SetChildrenDirty();
        }
    }

    void TransformComponent::SetScale(const Vector2f& scale)
    {
        if (localScale.x == scale.x && localScale.y == scale.y) return;

        localScale = scale;
        if (!isDirty)
        {
            isDirty = true;
            SetChildrenDirty();
        }
    }

    void TransformComponent::UpdateTransform()
    {
        // 1. Si estamos limpios, cortamos de raíz. ¡Costo cero!
        if (!isDirty) return;

        // 2. Calculamos nuestra propia matriz local
        Matrix3x3 t = Matrix3x3::Translation(localPosition);
        Matrix3x3 r = Matrix3x3::Rotation(localRotation * DEG2RAD);
        Matrix3x3 s = Matrix3x3::Scale(localScale);

        localMatrix = t * r * s;
        isDirty = false; // Ya estamos limpios localmente

        // 3. Calculamos nuestra matriz global
        if (owner != nullptr && owner->GetParent() != nullptr)
        {
            TransformComponent* parentTransform = owner->GetParent()->transform;

            // Si el padre está sucio, lo obligamos a calcularse antes de usar su matriz
            if (parentTransform->isDirty)
            {
                parentTransform->UpdateTransform();
            }

            // ¡Siempre heredamos el espacio del padre!
            globalMatrix = parentTransform->GetGlobalMatrix() * localMatrix;
        }
        else
        {
            // Somos el nodo raíz
            globalMatrix = localMatrix;
        }
    }

    const Matrix3x3& TransformComponent::GetGlobalMatrix()
    {
        return globalMatrix;
    }

    Vector2f TransformComponent::GetGlobalPosition()
    {
        // La posición global siempre está en la tercera columna de la matriz final (índices [0][2] y [1][2])
        return Vector2f(globalMatrix.m[0][2], globalMatrix.m[1][2]);
    }
}