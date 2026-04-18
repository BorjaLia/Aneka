#pragma once
#include <memory>
#include <string>

#include "events/eventBus.h"
#include "events/applicationEvents.h"
#include "events/audioEvents.h"
#include "resourceManager.h"
#include "IWindow.h"
#include "IAudio.h"
#include "sceneBuilder.h"
#include "../renderer/IRenderer.h"
#include "../input/IInput.h"
#include "math.h"
#include "node.h"
#include "core/scenes/sceneManager.h"

namespace Engine
{
    class PhysicsSystem;

    class Application
    {
    public:
        Application();
        virtual ~Application();

        static Application& Get() { return *s_Instance; }

        /// Initialises window, renderer, audio, and all engine systems.
        bool Initialize(Vector2i size, std::string title);

        /// Flushes the SceneBuilder, then runs the main game loop.
        void Run();

        /// Releases all systems cleanly.
        void Shutdown();

        // --- Scene authoring (use SceneBuilder in game.cpp) ---

        /// Returns the builder used to construct the scene before Run().
        SceneBuilder& GetSceneBuilder() { return sceneBuilder; }
        SceneManager& GetSceneManager() { return sceneManager; } // ¡NUEVO!
        // --- Engine system accessors ---

        ResourceManager* GetResourceManager() const { return resourceManager.get(); }
        EventBus&        GetEventBus()               { return eventBus; }
        Node*            GetRootScene()        const { return rootScene.get(); }
        IWindow*         GetWindow()           const { return window.get(); }
        IRenderer*       GetRenderer()         const { return window->GetRenderer(); }
        IInput*          GetInput()            const { return window->GetInput(); }
        IAudio*          GetAudio()            const { return audio.get(); }

        // --- State ---

        bool IsDebugMode() const { return debugMode; }
        void ToggleDebugMode();
        void MarkSceneDirty()       { isSceneDirty = true; }
        void MarkScenePendingStart(){ isScenePendingStart = true; }

        /// Walks the scene tree looking for an AudioListenerComponent. Returns the first node found.
        Node* FindAudioListener() const;

    private:
        static Application* s_Instance;

        std::unique_ptr<IWindow>          window;
        std::unique_ptr<IAudio>           audio;
        std::unique_ptr<ResourceManager>  resourceManager;
        std::unique_ptr<PhysicsSystem>    physicsSystem;

        EventBus eventBus;
        SceneBuilder sceneBuilder;
        SceneManager sceneManager;

        std::unique_ptr<Node> rootScene;
        std::unique_ptr<Node> debugNode;

        bool isRunning          = false;
        bool isSceneDirty       = false;
        bool isScenePendingStart = true;
        bool debugMode          = false;

        uint32_t muteEventId   = 0;
        uint32_t volumeEventId = 0;

        bool OnWindowClose(WindowCloseEvent& e);

        // Recursive helper for FindAudioListener
        static Node* FindListenerInTree(Node* node);
    };
}
