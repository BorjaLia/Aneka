#pragma once
#include "../Component.h"
#include "../scripts/script.h"
#include <memory>

namespace Engine
{
    class ScriptComponent : public Component
    {
    private:
        // El motor toma propiedad absoluta de la memoria del script del usuario
        std::unique_ptr<Script> script;

    public:
        // El constructor exige un script creado con 'new'
        ScriptComponent(Script* userScript);

        ~ScriptComponent() override;

        void Initialize() override;

        void Start() override;

        void Update(float deltaTime) override;

        void FixedUpdate(float fixedDeltaTime) override;

        // Utilidad opcional: Por si otro sistema necesita recuperar el script original
        template <typename T>
        T* GetScript() const;
    };
}