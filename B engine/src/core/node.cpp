#include "Node.h"
#include "Debug.h"
#include <algorithm> // Vital para std::remove_if
#include "Application.h"

namespace Engine
{

    void Node::NotifyEnginePendingStart()
    {
        Application::Get().MarkScenePendingStart();
    }

    Node::Node(const std::string& name) : name(name), parent(nullptr)
    {
        // 1. Instanciamos el TransformComponent obligatoriamente al nacer el Nodo
        auto newTransform = std::make_unique<TransformComponent>();
        transform = newTransform.get(); // Guardamos el atajo rápido

        // 2. Lo añadimos a la lista normal para que Update() y Draw() lo procesen
        newTransform->SetOwner(this);
        components.push_back(std::move(newTransform));
    }

    void Node::Destroy()
    {
        pendingDestruction = true;
        isActive = false; // Lo apagamos instantáneamente para que no se dibuje ni se mueva

        // Le avisamos al motor que al final del frame hay que limpiar
        Application::Get().MarkSceneDirty();

        if (!Application::Get().IsDebugMode()) { return; }

        ENGINE_LOG("DELETED: " << name);
    }

    void Node::CleanUp()
    {
        // 1. Limpiar Componentes de este Nodo
        components.erase(
            std::remove_if(components.begin(), components.end(),
                [](const std::unique_ptr<Component>& comp)
                {
                    return comp->IsPendingDestruction();
                }),
            components.end()
        );

        // 2. Limpiar Hijos de este Nodo
        children.erase(
            std::remove_if(children.begin(), children.end(),
                [](const std::unique_ptr<Node>& child)
                {
                    return child->IsPendingDestruction();
                }),
            children.end()
        );

        // 3. Propagar la limpieza a los hijos que sobrevivieron
        for (auto& child : children)
        {
            child->CleanUp();
        }
    }

    void Node::ClearChildren()
    {
        children.clear();
    }

    void Node::Start()
    {
        if (!isActive) return;

        // 1. Iniciamos los componentes recién nacidos
        for (auto& comp : components)
        {
            if (comp->IsActive() && !comp->HasStarted())
            {
                comp->Start(); // El equivalente a Awake/Start
                comp->SetStarted(true); // Marcamos para que no vuelva a llamarse jamás
            }
        }

        // 2. Propagamos a los hijos
        for (auto& child : children)
        {
            child->Start();
        }
    }

    void Node::Update(float deltaTime)
    {
        if (!isActive) return;
        // Obligamos a que el transform recalcule sus matrices antes de cualquier otra lógica
        transform->UpdateTransform();

        for (auto& comp : components)
        {
            // Saltamos el transform porque ya lo actualizamos manualmente arriba
            if (comp.get() != transform)
            {
                if (comp->IsActive())
                {
                    comp->Update(deltaTime);
                }
            }
        }

        for (auto& child : children)
        {
            child->Update(deltaTime);
        }
    }

    void Node::FixedUpdate(float fixedDeltaTime)
    {
        if (!isActive) return;

        for (auto& comp : components)
        {
            if (comp->IsActive() && comp.get() != transform)
            {
                comp->FixedUpdate(fixedDeltaTime);
            }
        }

        for (auto& child : children)
        {
            child->FixedUpdate(fixedDeltaTime);
        }
    }

    void Node::Draw(IRenderer* renderer)
    {
        if (!isActive) return;

        // 1. Dibujamos todos los componentes visuales de este nodo
        for (auto& comp : components)
        {
            if (comp->IsActive())
            {
                comp->Draw(renderer);
            }
        }

        // 2. Propagamos el Draw a todos los nodos hijos
        for (auto& child : children)
        {
            child->Draw(renderer);
        }
    }

    std::string Node::ToString() const
    {
        std::stringstream ss;
        ss << "Node: '" << name << "' | ";
        ss << "Pos Local: " << transform->GetPosition() << " | ";
        ss << "Pos Global: " << GetGlobalPosition() << "\n";

        ss << "  Children: " << children.size() << " | Components: " << components.size() << "\n";

        for (const auto& comp : components)
        {
            ss << "    -> " << comp->ToString() << "\n";
        }
        return ss.str();
    }

    void Node::DumpTree(int indentLevel) const
    {
        // Creamos un string con espacios multiplicados por el nivel de profundidad
        std::string indent(indentLevel * 2, ' ');

        // Imprimimos la información de ESTE nodo usando el ToString() que ya hiciste
        ENGINE_LOG(indent << "-> " << ToString());

        // Llamamos a la misma función en todos los hijos, sumando 1 a la profundidad
        for (const auto& child : children)
        {
            child->DumpTree(indentLevel + 1);
        }
    }

    void Node::AddChild(std::unique_ptr<Node> child)
    {
        child->parent = this;
        children.push_back(std::move(child)); // move transfiere la propiedad de la memoria
    }

    Node* Node::FindChild(std::string_view targetName) const
    {
        // 1. Buscamos en nuestros hijos directos
        for (const auto& child : children)
        {
            if (child->name == targetName)
            {
                return child.get();
            }
        }

        // 2. Si no lo encontramos, buscamos recursivamente en los hijos de nuestros hijos
        for (const auto& child : children)
        {
            Node* found = child->FindChild(targetName);
            if (found != nullptr)
            {
                return found;
            }
        }

        // 3. Si llegamos al final de la rama y no hay nada, retornamos null
        return nullptr;
    }

    Vector2f Node::GetGlobalPosition() const
    {
        return transform->GetGlobalPosition();
        //// Si somos la raíz o no tenemos padre, lo local es lo global
        //if (parent == nullptr)
        //{
        //    return transform->GetPosition();
        //}

        //// Si tenemos padre, sumamos nuestra posición local a la posición global del padre
        //Vector2f parentGlobal = parent->GetGlobalPosition();
        //Vector2f localPos = transform->GetPosition();

        //return Engine::Vector2f{
        //    parentGlobal.x + localPos.x,
        //    parentGlobal.y + localPos.y
        //};
    }

    void Node::GetAllCameras(std::vector<CameraComponent*>& outCameras)
    {
        // 1. Revisamos si este nodo tiene una cámara
        CameraComponent* cam = GetComponent<CameraComponent>();
        if (cam != nullptr)
        {
            outCameras.push_back(cam);
        }

        // 2. Le preguntamos a todos los hijos recursivamente
        for (auto& child : children)
        {
            child->GetAllCameras(outCameras);
        }
    }
    void Node::GetAllColliders(std::vector<ColliderComponent*>& outColliders)
    {
        // 1. ¿Estoy activo? Si no, ni yo ni mis hijos tenemos colisiones
        if (!isActive) return;

        // 2. ¿Tengo un collider activo?
        if (auto* col = GetComponent<ColliderComponent>())
        {
            if (col->IsActive())
            {
                outColliders.push_back(col);
            }
        }

        // 3. Propagar a los hijos
        for (auto& child : children)
        {
            child->GetAllColliders(outColliders);
        }
    }

    void Node::GetAllTriggerAreas(std::vector<TriggerAreaComponent*>& outTriggerAreas)
    {
        // 1. ¿Estoy activo? Si no, ni yo ni mis hijos tenemos colisiones
        if (!isActive) return;

        // 2. ¿Tengo un collider activo?
        if (auto* col = GetComponent<TriggerAreaComponent>())
        {
            if (col->IsActive())
            {
                outTriggerAreas.push_back(col);
            }
        }

        // 3. Propagar a los hijos
        for (auto& child : children)
        {
            child->GetAllTriggerAreas(outTriggerAreas);
        }
    }
}