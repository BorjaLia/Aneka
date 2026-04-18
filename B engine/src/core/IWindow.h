#pragma once
#include <memory>
#include <string>
#include <functional>
#include "Events/Event.h"
#include "../Renderer/IRenderer.h"
#include "../Input/IInput.h"
#include "math.h"

namespace Engine
{
    class IWindow
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~IWindow() = default;

        virtual bool Initialize(const Vector2i& size, const std::string& title) = 0;
        virtual void Shutdown() = 0;

        // Obligamos a todas las ventanas a tener estas funciones básicas
        virtual void OnUpdate() = 0;

        virtual Vector2i GetSize() const = 0;
        
        virtual bool WindowShouldClose() const = 0;

        virtual void SetTitle(const std::string& title) = 0;
        virtual void SetTargetFPS(int fps) = 0;
        virtual void SetFullscreen(bool fullscreen) = 0;
        virtual bool IsFullscreen() const = 0;
        virtual void SetVSync(bool vsync) = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        // La ventana será la proveedora de los sistemas que dependen del hardware
        virtual IRenderer* GetRenderer() const = 0;
        virtual IInput* GetInput() const = 0;

        // Podríamos añadir una función estática Create() en el futuro
        // static std::unique_ptr<IWindow> Create(const Vector2i& size, const std::string& title);
    };
}