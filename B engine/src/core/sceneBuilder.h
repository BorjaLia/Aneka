#pragma once
#include "node.h"
#include "types.h"
#include <memory>
#include <vector>

namespace Engine
{
    class Application;

    /// Fluent helper for constructing scenes in game.cpp.
    /// Call CreateNode() to get a raw pointer you can configure immediately.
    /// All created nodes are flushed into the root scene by Application::Run()
    /// before the first frame — you never need to call AddChild manually.
    class SceneBuilder
    {
    public:
        SceneBuilder() = default;


        /// Creates a new node, retains ownership, and returns a raw pointer for configuration.
        /// The node is added to the root scene automatically before the game loop starts.
        Node* CreateNode(const std::string& name = "Node");

        /// Creates a node that is a child of an already-created node.
        /// @param parent  Must be a pointer previously returned by CreateNode().
        Node* CreateChildNode(Node* parent, const std::string& name = "Node");

        Node* FindPending(const std::string& name);
        
        /// Called once by Application::Run() — moves all top-level nodes into the root scene.
        /// Do not call this from game code.
        void FlushToScene(Node* rootScene);


    private:
        // Owns nodes until FlushToScene transfers them to the root scene.
        
        struct PendingNode
        {
            std::unique_ptr<Node> node;
            Node* parent; // Si es nullptr, significa que va al RootScene
        };

        std::vector<PendingNode> pendingNodes;

        //std::vector<std::unique_ptr<Node>> pendingNodes;
    };
}
