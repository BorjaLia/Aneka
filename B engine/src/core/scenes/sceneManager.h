#pragma once
#include <memory>
#include "Scene.h"

namespace Engine
{
    class SceneManager
    {
    private:
        std::unique_ptr<IScene> pendingScene = nullptr;
        bool hasPendingScene = false;

    public:
        SceneManager() = default;
        ~SceneManager() = default;

        // Guarda la escena y levanta la bandera de "cambio solicitado"
        void LoadScene(std::unique_ptr<IScene> newScene);

        bool HasPendingScene() const { return hasPendingScene; }

        // Extrae la escena y baja la bandera
        std::unique_ptr<IScene> ConsumePendingScene();
    };
}