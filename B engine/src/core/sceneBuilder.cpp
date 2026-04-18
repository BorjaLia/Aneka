#include "sceneBuilder.h"
#include "node.h"
#include "application.h"
#include "debug.h"

namespace Engine
{
    Node* SceneBuilder::CreateNode(const std::string& name)
    {
        auto node = std::make_unique<Node>(name);
        Node* raw = node.get();
        pendingNodes.push_back({ std::move(node),nullptr });
        return raw;
    }

    Node* SceneBuilder::CreateChildNode(Node* parent, const std::string& name)
    {
        // The child is owned by its parent node, not by pendingNodes.
        auto child = std::make_unique<Node>(name);
        Node* raw  = child.get();
        pendingNodes.push_back({std::move(child),parent });
        return raw;
    }

    Node* SceneBuilder::FindPending(const std::string& name)
    {
        for (auto& node : pendingNodes)
        {
            Node* current = node.node.get();
            if (current->name == name) return current;
            Node* found = current->FindChild(name);
            if (found) return found;
        }

        ENGINE_WARN("Penging node not found!");

        return nullptr;
    }


    void SceneBuilder::FlushToScene(Node* rootScene)
    {
        if (pendingNodes.empty()) return;

        bool nodesAdded = false;

        for (auto& pending : pendingNodes)
        {
            if (pending.parent == nullptr)
            {
                rootScene->AddChild(std::move(pending.node));
            }
            else
            {
                pending.parent->AddChild(std::move(pending.node));
            }
            nodesAdded = true;
        }

        // Limpiamos la lista de espera
        pendingNodes.clear();

        // ¡MAGIA! Si añadimos nodos, le avisamos a la app para que les haga Start() 
        // en el próximo ciclo, tal como ya lo tenías diseñado.
        if (nodesAdded)
        {
            Application::Get().MarkScenePendingStart();
        }
    }
}
