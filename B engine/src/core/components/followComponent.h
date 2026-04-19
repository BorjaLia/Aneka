#pragma once
#include "../Component.h"
#include "../Types.h"
#include <cmath>

namespace Engine
{
    class Node;

    enum class FollowMode
    {
        Strict,
        Lerp,
        Linear
    };

    class FollowComponent : public Component
    {
    private:
        Node* target = nullptr;
        FollowMode mode = FollowMode::Lerp;

        Vector2f offset{ 0.0f, 0.0f };
        float lerpSpeed = 5.0f; 

        float snapDistance = 0.5f;
        float maxDistance = 300.0f;

    public:
        FollowComponent(Node* targetNode = nullptr, FollowMode followMode = FollowMode::Lerp, float speed = 5.0f);
        ~FollowComponent() override = default;

        void Update(float deltaTime) override;

        std::string ToString() const override;

        void SetTarget(Node* t) { target = t; }
        void SetMode(FollowMode m) { mode = m; }
        void SetOffset(const Vector2f& off) { offset = off; }
        void SetLerpSpeed(float speed) { lerpSpeed = speed; }
        void SetConstraints(float snap, float maxDist) { snapDistance = snap; maxDistance = maxDist; }

        Node* GetTarget() const { return target; }
    };
}