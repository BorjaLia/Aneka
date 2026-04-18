#include "FollowComponent.h"
#include "../Node.h"
#include "TransformComponent.h"

namespace Engine
{
    FollowComponent::FollowComponent(Node* targetNode, FollowMode followMode, float speed)
        : target(targetNode), mode(followMode), lerpSpeed(speed)
    {
    }

    void FollowComponent::Update(float deltaTime)
    {
        // Si no hay objetivo, o a nosotros nos falta el transform, no hacemos nada
        if (!owner || !target || !owner->transform || !target->transform) return;

        // Asumimos que el perseguidor (ej: Cámara) está en la raíz, por lo que su posición local es global.
        Vector2f currentPos = owner->transform->GetPosition();

        // Obtenemos la posición real global del objetivo en este frame
        Vector2f targetPos = target->GetGlobalPosition() + offset;

        Vector2f diff = targetPos - currentPos;
        float distSq = diff.MagnitudeSquared();

        // 1. Lógica de "Snap" (Evitar cálculos infinitos cuando ya estamos casi encima)
        if (snapDistance > 0.0f && distSq <= (snapDistance * snapDistance))
        {
            owner->transform->SetPosition(targetPos);
            return;
        }

        // 2. Lógica de Distancia Máxima (Arrastre forzado)
        if (maxDistance > 0.0f && distSq > (maxDistance * maxDistance))
        {
            float dist = std::sqrt(distSq);
            Vector2f dir = diff / dist; // Vector normalizado

            // Empujamos nuestra posición actual para no superar el límite máximo
            currentPos = targetPos - (dir * maxDistance);
            owner->transform->SetPosition(currentPos);

            // Recalculamos la diferencia para el Lerp desde el nuevo límite
            diff = targetPos - currentPos;
        }

        // 3. Aplicar el Movimiento
        if (mode == FollowMode::Strict)
        {
            owner->transform->SetPosition(targetPos);
        }
        else if (mode == FollowMode::Lerp)
        {
            // Fórmula mágica de Lerp independiente del Framerate:
            // position += diff * (1.0 - exp(-speed * deltaTime))
            float t = 1.0f - std::exp(-lerpSpeed * deltaTime);

            Vector2f newPos = currentPos + (diff * t);
            owner->transform->SetPosition(newPos);
        }
    }
    std::string FollowComponent::ToString() const
    {
        std::stringstream ss;
        ss << "Follow [Speed " << lerpSpeed;


        if (mode == FollowMode::Strict)
        {
            ss << " | Follow mode: ( Strict )";
        }
        else if (mode == FollowMode::Lerp)
        {
            ss << " | Follow mode: ( Lerp )";
        }


        ss << "]";
        return ss.str();
    }
}