#pragma once
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>
#include "Types.h"
#include "Component.h"
#include "components/transformComponent.h"
#include "components/cameraComponent.h"
#include "components/colliderComponent.h"
#include "components/triggerAreaComponent.h"

#include "debug.h"

namespace Engine
{
    class IRenderer;

    class Node
    {
    private:
        bool isActive = true; // Encendido por defecto
        bool pendingDestruction = false; // El sticker

        void NotifyEnginePendingStart();
    public:
        std::string name;

        TransformComponent* transform;

        Node(const std::string& name = "Node");
        virtual ~Node() = default;

        bool IsActive() const { return isActive; }
        void SetActive(bool active) { isActive = active; }

        bool IsPendingDestruction() const { return pendingDestruction; }
        virtual void Destroy();
        virtual void CleanUp();
        void ClearChildren();

        // El motor llamará a estos métodos en cada frame
        void Start();
        void Update(float deltaTime);
        void FixedUpdate(float fixedDeltaTime);
        void Draw(IRenderer* renderer);

        std::string ToString() const;
        void DumpTree(int indentLevel = 0) const;

        // --- MANEJO DE JERARQUÍA ---
        void AddChild(std::unique_ptr<Node> child);
        Node* FindChild(std::string_view targetName) const;
        Node* GetParent() const { return parent; }

        const std::vector<std::unique_ptr<Node>>& GetChildren() const { return children; }

        Vector2f GetGlobalPosition() const;
        // --- MANEJO DE COMPONENTES (Magia de Templates) ---
        // Este método nos permite añadir componentes así: miNodo->AddComponent<SpriteComponent>(textura);
        template <typename T, typename... Args>
        T* AddComponent(Args&&... args)
        {
            // Creamos el componente pasándole los argumentos que necesite su constructor
            auto newComponent = std::make_unique<T>(std::forward<Args>(args)...);
            newComponent->SetOwner(this);

            T* rawPtr = newComponent.get(); // Guardamos un puntero crudo para devolverlo

            components.push_back(std::move(newComponent)); // El Node toma posesión de la memoria

            rawPtr->Initialize();

            NotifyEnginePendingStart();

            //rawPtr->Initialize(); // Inicializamos el componente apenas se añade
            return rawPtr;
        }

        // Método para buscar un componente específico en este nodo
        template <typename T>
        T* GetComponent()
        {
            for (auto& comp : components)
            {
                // dynamic_cast comprueba si el componente actual es del tipo T que buscamos
                T* target = dynamic_cast<T*>(comp.get());
                if (target != nullptr)
                {
                    return target;
                }
            }
            //ENGINE_WARN("No component found!");
            return nullptr; // Retorna null si el nodo no tiene este componente
        }

        void GetAllCameras(std::vector<CameraComponent*>& outCameras);
        void GetAllColliders(std::vector<ColliderComponent*>& outColliders);
        void GetAllTriggerAreas(std::vector<TriggerAreaComponent*>& outTriggerAreas);
        const std::vector<std::unique_ptr<Component>>& GetAllComponents() const { return components; }

    private:
        std::vector<std::unique_ptr<Component>> components;
        std::vector<std::unique_ptr<Node>> children;
        Node* parent = nullptr;
    };
}