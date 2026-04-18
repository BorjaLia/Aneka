#include "playerMovementComponent.h"
#include "../Node.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "../Events/GameEvents.h" 
#include "../Application.h" // ¡Global access!
#include <sstream>

namespace Engine
{
    PlayerMovementComponent::PlayerMovementComponent(float speed, MovementKeys customKeys)
        : speed(speed), keys(customKeys)
    {
    }

    void PlayerMovementComponent::Start()
    {
        if (owner)
        {
            animator = owner->GetComponent<AnimatedSpriteComponent>();
        }
    }

    void PlayerMovementComponent::Update(float deltaTime)
    {
        auto* input = Application::Get().GetInput();
        if (owner == nullptr || input == nullptr) return;

        Vector2f direction(0.0f, 0.0f);

        if (input->IsKeyDown(keys.up))    direction.y += 1.0f;
        if (input->IsKeyDown(keys.down))  direction.y -= 1.0f;
        if (input->IsKeyDown(keys.left))  direction.x -= 1.0f;
        if (input->IsKeyDown(keys.right)) direction.x += 1.0f;

        if (direction.MagnitudeSquared() > 0)
        {
            direction = direction.Normalized();

            Vector2f currentPos = owner->transform->GetPosition();
            Vector2f newPos = currentPos + (direction * speed * deltaTime);
            owner->transform->SetPosition(newPos);

            // Avisamos al motor globalmente
            PlayerMovedEvent movedEvent(newPos);
            Application::Get().GetEventBus().Publish(movedEvent);

            // Actualizamos la animación opcional
            if (animator)
            {
                animator->Play("Run");
                if (direction.x != 0.0f) animator->SetFlipX(direction.x < 0);
                animator->speedMultiplier = 1.0f; // Podría ser modulado por buffs de velocidad
            }
        }
        else
        {
            if (animator)
            {
                animator->Play("Idle");
                animator->speedMultiplier = 1.0f;
            }
        }
    }

    std::string PlayerMovementComponent::ToString() const
    {
        std::stringstream ss;
        ss << "PlayerMovementComponent [Speed: " << speed << "]";
        return ss.str();
    }
}