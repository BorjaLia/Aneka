#include "core/MemoryTracker.h"

#include "Application.h"
#include "../Renderer/RaylibRenderer.h"
#include "../Input/RaylibInput.h"
#include "../Window/raylibWindow.h"
#include "../../src/platform/rayLib/raylibAudio.h"
#include "time.h"
#include "../Physics/PhysicsSystem.h"
#include "../core/components/colliderComponent.h"
#include "../core/components/textComponent.h"
#include "../core/components/uiAnchorComponent.h"
#include "../core/components/audioListenerComponent.h"
#include "debug.h"
#include <iostream>

namespace Engine
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;
        rootScene  = std::make_unique<Node>("Root");
        debugNode  = std::make_unique<Node>("Debug");

        eventBus.Subscribe<WindowCloseEvent>([this](WindowCloseEvent& e) { OnWindowClose(e); });
    }

    Application::~Application() {}

    bool Application::Initialize(Vector2i size, std::string title)
    {
        window = std::make_unique<RaylibWindow>();
        window->SetEventCallback([this](Event& e) { eventBus.Publish(e); });

        if (!window->Initialize(size, title)) return false;

        // Audio initialised before ResourceManager so RM can pass the pointer in.
        auto raylibAudio = std::make_unique<RaylibAudio>();
        if (raylibAudio->Initialize())
        {
            audio = std::move(raylibAudio);
        }
        else
        {
            ENGINE_WARN("Application: Audio device failed to initialise. Audio disabled.");
        }

        // Global audio event handlers — components may also subscribe individually.
        muteEventId = eventBus.Subscribe<AudioMuteEvent>([this](AudioMuteEvent& e)
        {
            if (audio) audio->SetMasterMuted(e.GetMute());
        });

        volumeEventId = eventBus.Subscribe<AudioVolumeEvent>([this](AudioVolumeEvent& e)
        {
            if (audio) audio->SetMasterVolume(e.GetVolume());
        });

        resourceManager = std::make_unique<ResourceManager>(window->GetRenderer(), audio.get());
        physicsSystem   = std::make_unique<PhysicsSystem>();

        // Debug FPS node (lives outside rootScene so it's unaffected by TimeScale)
        Font* debugFont = resourceManager->GetFont("res/fonts/ReemKufiFunRegular.ttf", 48);
        debugNode->AddComponent<UIAnchorComponent>();
        debugNode->AddComponent<TextComponent>(debugFont, "FPS: 0", 32.0f,
                                               Color{ 0, 255, 0, 255 }, RenderLayer::UI);
        debugNode->SetActive(false);

        isRunning = true;
        return true;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        isRunning = false;
        e.handled = true;
        return true;
    }

    void Application::Run()
    {
        // Flush any nodes built via SceneBuilder before the first frame.
        sceneBuilder.FlushToScene(rootScene.get());

        Color bgColor(50, 50, 60, 255);

        IRenderer* renderer = window->GetRenderer();
        IInput*    input    = window->GetInput();

        std::vector<CameraComponent*> activeCameras;

        const float FIXED_TIMESTEP = 1.0f / 60.0f;
        float accumulator = 0.0f;
        float fpsTimer    = 0.0f;
        int   frameCount  = 0;
        int   currentFPS  = 0;

        while (isRunning)
        {
            window->OnUpdate();
            if (!isRunning) break;

            if (sceneManager.HasPendingScene())
            {
                // A. Aniquilamos todo el nivel actual (liberando RAM instantáneamente)
                rootScene->ClearChildren();

                // B. Extraemos la nueva escena
                auto newScene = sceneManager.ConsumePendingScene();

                // C. Ejecutamos la receta de construcción de la nueva escena
                if (newScene)
                {
                    newScene->Build(sceneBuilder);
                }
                accumulator = 0.0f;
            }

            sceneBuilder.FlushToScene(rootScene.get());

            float rawDt = renderer->GetDeltaTime();
            if (rawDt > 0.25f) rawDt = 0.25f;
            Time::Update(rawDt);

            // FPS counter uses unscaled time so it's accurate even when paused.
            fpsTimer += Time::GetUnscaledDeltaTime();
            if (++frameCount, fpsTimer >= 1.0f)
            {
                currentFPS = frameCount;
                frameCount = 0;
                fpsTimer  -= 1.0f;
                debugNode->GetComponent<TextComponent>()->SetText("FPS: " + std::to_string(currentFPS));
            }

            accumulator += Time::GetDeltaTime();

            // Lazy Start — fires once, and again whenever new nodes are added mid-game.
            if (isScenePendingStart)
            {
                rootScene->Start();
                isScenePendingStart = false;
            }

            // Fixed-timestep physics loop.
            while (accumulator >= FIXED_TIMESTEP)
            {
                rootScene->FixedUpdate(FIXED_TIMESTEP);
                if (physicsSystem) physicsSystem->Update(rootScene.get(), FIXED_TIMESTEP);
                accumulator -= FIXED_TIMESTEP;
            }

            if (input->IsKeyReleased(Key::F3)) ToggleDebugMode();

            rootScene->Update(Time::GetDeltaTime());

            if (input->IsKeyReleased(Key::F4)) rootScene->DumpTree();

            // Draw — fills render queues.
            rootScene->Draw(renderer);
            if (debugNode->IsActive()) debugNode->Draw(renderer);

            // Render — flush queues to GPU.
            renderer->BeginFrame();
            renderer->ClearScreen(bgColor);

            activeCameras.clear();
            rootScene->GetAllCameras(activeCameras);

            for (CameraComponent* cam : activeCameras)
            {
                if (cam->HasRenderTarget())
                {
                    renderer->BeginRenderToTexture(cam->GetRenderTarget());
                    renderer->ClearScreen(bgColor);
                }

                renderer->BeginCamera(cam->GetOwner()->GetGlobalPosition(), cam->GetZoom());
                renderer->Flush(RenderLayer::World);
                if (cam->GetShowDebug()) renderer->FlushDebug(RenderLayer::World);
                renderer->EndCamera();

                if (cam->HasRenderTarget()) renderer->EndRenderToTexture();
            }

            renderer->Flush(RenderLayer::UI);
            if (debugMode) renderer->FlushDebug(RenderLayer::UI);
            renderer->EndFrame();

            if (isSceneDirty)
            {
                rootScene->CleanUp();
                isSceneDirty = false;
            }
        }
    }

    void Application::Shutdown()
    {
        if (audio)  audio->Shutdown();
        if (window) window->Shutdown();
    }

    void Application::ToggleDebugMode()
    {
        debugMode = !debugMode;
        debugNode->SetActive(debugMode);
        if (window && window->GetRenderer())
            window->GetRenderer()->SetDebugRenderEnabled(debugMode);
        ENGINE_LOG("Debug mode: " << (debugMode ? "ON" : "OFF"));
    }

    Node* Application::FindAudioListener() const
    {
        return FindListenerInTree(rootScene.get());
    }

    Node* Application::FindListenerInTree(Node* node)
    {
        if (!node) return nullptr;
        if (node->GetComponent<AudioListenerComponent>()) return node;
        for (const auto& child : node->GetChildren())
        {
            Node* found = FindListenerInTree(child.get());
            if (found) return found;
        }
        return nullptr;
    }
}
