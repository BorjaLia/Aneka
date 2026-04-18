#pragma once
#include "core/sceneBuilder.h"

namespace Engine
{
    class IScene
    {
    public:
        virtual ~IScene() = default;

        // Esta es la función mágica donde programarás cada nivel
        virtual void Build(SceneBuilder& builder) = 0;
    };
}