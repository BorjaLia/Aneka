#pragma once
#include "../Component.h"
#include "../../input/keyCodes.h"
#include "../src/physics/ICollisionListener.h"

namespace Engine
{
    class RigidBodyComponent;
    class AnimatedSpriteComponent; // Declaración adelantada

    struct PlatformerKeys
    {
        Key left = Key::A;
        Key right = Key::D;
        Key jump = Key::Space;
        Key run = Key::LeftShift;
        Key rotLeft = Key::Q;
        Key rotRight = Key::E;
    };

    class PhysicsPlayerController : public Component, public ICollisionListener
    {
    private:
        RigidBodyComponent* rigidBody = nullptr;
        AnimatedSpriteComponent* animator = nullptr; // ¡Nuevo!

        float walkSpeed = 300.0f;
        float runSpeed = 500.0f;
        float jumpForce = 500.0f;
        float torqueForce = 3000.0f;

        PlatformerKeys keys;

        bool isRunning = false;

        bool isGrounded = true;
        bool jumpRequested = false;

        bool touchingLeftWall = false;
        bool touchingRightWall = false;

    public:
        // ¡LIMPIO! Ya no inyectamos IInput ni EventBus
        PhysicsPlayerController(float walkSpd = 300.0f, float runSpd = 500.0f, float jumpFrc = 500.0f, PlatformerKeys customKeys = {});
        ~PhysicsPlayerController() override = default;

        void Start()                         override;
        void FixedUpdate(float fixedDeltaTime) override;
        void Update(float deltaTime)           override;
        void OnCollision(const Physics::CollisionManifold& hit) override;

        void SetKeys(const PlatformerKeys& newKeys) { keys = newKeys; }
        void SetTorqueForce(float f) { torqueForce = f; }

        float GetWalkSpeed() { return walkSpeed; };
        float GetRunSpeed() { return runSpeed; };

        bool IsRunning() { return isRunning; };

        void SetGrounded(bool setGrounded) { isGrounded = setGrounded; };
        bool GetGrounded() { return isGrounded; };

        bool GetJumpRequested() { return jumpRequested; };
    };
}