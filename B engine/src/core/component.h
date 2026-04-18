#pragma once
#include <string>

namespace Engine
{

    class Node; // Forward declaration: Le decimos al compilador que "Node" existe para poder usar el puntero
    class IRenderer;

    class Component
    {
    private:
        bool isActive = true; // Encendido por defecto
        bool hasStarted = false;
        bool pendingDestruction = false; // El sticker

    protected:
        Node* owner = nullptr; // Puntero al nodo que "posee" este componente

    public:
        virtual ~Component() = default;

        bool IsActive() const { return isActive; }
        void SetActive(bool active) { isActive = active; }
        
        bool HasStarted() const { return hasStarted; }
        void SetStarted(bool started) { hasStarted = started; }

        bool IsPendingDestruction() const { return pendingDestruction; }
        void Destroy();

        // Ciclo de vida básico de cualquier componente
        virtual void Initialize() {}
        virtual void Start() {}
        virtual void FixedUpdate(float fixedDeltaTime) { fixedDeltaTime = 0.0f; } // NUEVO
        virtual void Update(float deltaTime) { deltaTime = 0.0f; }
        virtual void Draw(IRenderer* renderer) { renderer = nullptr; }

        virtual std::string ToString() const { return "Component"; }

        // Setters y Getters para el dueño
        void SetOwner(Node* node) { owner = node; }
        Node* GetOwner() const { return owner; }
    };
}