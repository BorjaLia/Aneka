#include "TriggerAreaComponent.h"
#include "../Node.h"
#include "../../renderer/IRenderer.h"
#include "spriteComponent.h"
#include "animatedSpriteComponent.h"

namespace Engine
{
    TriggerAreaComponent::TriggerAreaComponent(const Shape& initialShape, const Vector2f& offset, bool autoFit, const Color& color)
        : shape(initialShape), offset(offset), autoFitToSprite(autoFit), debugColor(color)
    {
    }

    void TriggerAreaComponent::Start()
    {

        // ¡El Early Exit! Si no queremos autoajuste o si por algún error no hay dueño, nos vamos.
        if (!autoFitToSprite || owner == nullptr) return;
        // Si marcamos autoFitToSprite, calculamos todo UNA SOLA VEZ al nacer
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
                baseSize = animator->GetCurrentFrameSize(); // Usamos la nueva función
            }
            else
            {
                pivot = sprite->pivot;
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

            // 4. ¡LA MAGIA DEL PIVOTE!
            Vector2f pivotMult = GetPivotMultiplier(pivot);

            offset.x = (0.5f - pivotMult.x) * finalWidth;
            // ¡CORREGIDO!: Sin el signo negativo para 2D Y-Down
            offset.y = (0.5f - pivotMult.y) * finalHeight;
        }
    }

    void TriggerAreaComponent::Draw(IRenderer* renderer)
    {
        if (owner == nullptr || renderer == nullptr) return;

        Vector2f globalPos = owner->GetGlobalPosition();
        Vector2f triggerPos = { globalPos.x + offset.x, globalPos.y + offset.y };

        float rot = owner->transform->GetRotation();

        renderer->SubmitDebugShape(RenderLayer::World, shape, triggerPos,rot, debugColor);
    }
}