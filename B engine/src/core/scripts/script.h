#pragma once

namespace Engine
{
    class Node; // Forward declaration

    // La clase base que los usuarios heredarán (El equivalente a MonoBehaviour en Unity)
    class Script
    {
    protected:
        // ¡Protegido para que las clases hijas puedan acceder a su propio Nodo libremente!
        Node* owner = nullptr;

    public:
        virtual ~Script() = default;

        // El ciclo de vida que el usuario puede sobrescribir
        virtual void OnStart() {}
        virtual void OnUpdate(float deltaTime) { (void)deltaTime; }
        virtual void OnFixedUpdate(float fixedDeltaTime) { (void)fixedDeltaTime; }
        virtual void OnDestroy() {}

        // Función interna usada por el motor para inyectar la dependencia
        void SetOwner(Node* node) { owner = node; }
        Node* GetOwner() const { return owner; }
    };
}