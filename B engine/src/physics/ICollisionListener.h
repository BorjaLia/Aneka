#pragma once
#include "Physics.h" // O donde sea que esté definido tu CollisionManifold

namespace Engine
{
    class ICollisionListener
    {
    public:
        virtual ~ICollisionListener() = default;

        // Usamos el nombre exacto de tu estructura
        virtual void OnCollision(const Physics::CollisionManifold& hit) = 0;
    };
}