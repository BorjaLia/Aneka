#pragma once
#include "../Component.h"
#include "../Types.h"
#include <string>

namespace Engine
{

    class DebugTrackingComponent : public Component
    {
    private:
        Vector2f lastPosition;
        bool wasMoving;

    public:
        DebugTrackingComponent();
        ~DebugTrackingComponent() override = default;

        void Update(float deltaTime) override;

        // ¡Aprovechamos de incluir el ToString que acabamos de diseñar!
        std::string ToString() const override;
    };

}