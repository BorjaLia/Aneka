#pragma once
#include "../Core/IWindow.h"

namespace Engine
{

    class RaylibWindow : public IWindow
    {
    private:
        std::unique_ptr<IRenderer> renderer;
        std::unique_ptr<IInput> input;
        EventCallbackFn eventCallback;

        struct WindowData
        {
            std::string title;
            Vector2i size;
        } data;

    public:
        RaylibWindow();
        ~RaylibWindow() override;

        bool Initialize(const Vector2i& size, const std::string& title) override;
        void Shutdown() override;

        void OnUpdate() override;

        inline Vector2i GetSize() const override { return data.size; }

        virtual bool WindowShouldClose() const override;

        // Funciones del Sistema Operativo (Migradas del Renderer)
        void SetTitle(const std::string& title) override;
        void SetTargetFPS(int fps) override;
        void SetFullscreen(bool fullscreen) override;
        bool IsFullscreen() const override;
        void SetVSync(bool vsync) override;

        inline void SetEventCallback(const EventCallbackFn& callback) override { eventCallback = callback; }

        inline IRenderer* GetRenderer() const override { return renderer.get(); }
        inline IInput* GetInput() const override { return input.get(); }
    };
}