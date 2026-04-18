#pragma once
#include "../Component.h"
#include "../../Input/IInput.h"
#include <array>

namespace Engine
{
    class AnimatedSpriteComponent; // Declaración adelantada

    struct MovementKeys
    {
        Key up = Key::W;
        Key down = Key::S;
        Key left = Key::A;
        Key right = Key::D;
    };

    class PlayerMovementComponent : public Component
    {
    private:
        AnimatedSpriteComponent* animator = nullptr;
        float speed;
        MovementKeys keys;

    public:
        // ¡LIMPIO! Sin dependencias inyectadas
        PlayerMovementComponent(float speed = 200.0f, MovementKeys customKeys = {});
        ~PlayerMovementComponent() override = default;

        void Start() override; // Necesario para buscar el Animator
        void Update(float deltaTime) override;

        std::string ToString() const override;

        void SetKeys(const MovementKeys& newKeys) { keys = newKeys; }
    };
}