#include "ColliderComponent.h"
#include "../Node.h"
#include "../../renderer/IRenderer.h"
#include "spriteComponent.h"
#include "animatedSpriteComponent.h"

namespace Engine
{
    ColliderComponent::ColliderComponent(const Shape& initialShape, const Vector2f& offset, bool autoFit, const Color& color)
        : shape(initialShape), offset(offset), autoFitToSprite(autoFit), debugColor(color)
    {
    }

    void ColliderComponent::Start()
    {
        if (!autoFitToSprite || owner == nullptr) return;

        if (autoFitToSprite && owner)
        {
            auto* sprite = owner->GetComponent<SpriteComponent>();
            auto* animator = owner->GetComponent<AnimatedSpriteComponent>();

            // Si no tiene ninguno de los dos, salimos
            if (!animator && !sprite) return;

            Engine::Pivot pivot;
            Vector2f baseSize; // Guardamos el tamaño base (Frame o Textura)

            if (animator)
            {
                pivot = animator->pivot;

                Vector2f target = animator->GetTargetSize();

                if (target.x != 0.0f && target.y != 0.0f)
                    baseSize = target; // Usamos el tamaño forzado
                else
                    baseSize = animator->GetCurrentFrameSize(); // Usamos el tamaño original del frame
            }
            else
            {
                pivot = sprite->pivot;
                Vector2f target = sprite->GetTargetSize();

                if (target.x != 0.0f && target.y != 0.0f)
                    baseSize = target; // Usamos el tamaño forzado
                else
                    baseSize = { static_cast<float>(sprite->texture.size.x), static_cast<float>(sprite->texture.size.y) };
            }

            // 1. Obtenemos la escala final del Transform
            Vector2f scale = owner->transform->GetScale();

            // 2. Calculamos el tamaño real escalado basado en 'baseSize'
            float finalWidth = baseSize.x * std::abs(scale.x);
            float finalHeight = baseSize.y * std::abs(scale.y);

            // 3. Horneamos el tamaño final en la figura (Shape)
            if (std::holds_alternative<RectangleShape>(shape))
            {
                shape = RectangleShape{ {finalWidth, finalHeight} };
            }
            else if (std::holds_alternative<CircleShape>(shape))
            {
                shape = CircleShape{ std::max(finalWidth, finalHeight) / 2.0f };
            }

            Vector2f pivotMult = GetPivotMultiplier(pivot);

            offset.x = (0.5f - pivotMult.x) * finalWidth;
            offset.y = (0.5f - pivotMult.y) * finalHeight;
        }
    }

    void ColliderComponent::Draw(IRenderer* renderer)
    {
        if (owner == nullptr || renderer == nullptr) return;

        Vector2f globalPos = owner->GetGlobalPosition();
        Vector2f colliderPos = { globalPos.x + offset.x, globalPos.y + offset.y };


        float rot = owner->transform->GetRotation();

        // OJO: Le mandamos la forma ESCALADA al debug renderer
        renderer->SubmitDebugShape(RenderLayer::World, GetShape(), colliderPos,rot, debugColor);
    }
}