#include "RaylibWindow.h"
#include "renderer/raylibRenderer.h"
#include "input/RaylibInput.h"
#include "../Core/Events/ApplicationEvents.h"
#include "../Core/Events/inputEvents.h"
#include <raylib.h> // Único lugar donde existe raylib

namespace Engine
{
    RaylibWindow::RaylibWindow()
    {
        data.size = Vector2i(0, 0);
        data.title = "";
    }

    RaylibWindow::~RaylibWindow()
    {
        Shutdown();
    }

    bool RaylibWindow::Initialize(const Vector2i& size, const std::string& title)
    {

        // Set the minimum log level to display. 
        // LOG_ERROR will hide all INFO and WARNING messages.
        // LOG_NONE will hide everything including errors.
        ::SetTraceLogLevel(LOG_NONE);


        data.size = size;
        data.title = title;

        // 1. ¡La Ventana pide permiso al Sistema Operativo!
        ::InitWindow(size.x, size.y, title.c_str());

        ::SetExitKey(KEY_NULL);

        // Validamos si el SO nos dio la ventana
        if (!::IsWindowReady())
        {
            return false;
        }

        // 2. Ahora que hay un contexto gráfico, creamos los obreros
        renderer = std::make_unique<RaylibRenderer>();
        input = std::make_unique<RaylibInput>();

        ::SetWindowState(FLAG_WINDOW_RESIZABLE);

        // 3. Inicializamos al obrero gráfico
        if (!renderer->Initialize())
        {
            return false;
        }

        return true;
    }

    void RaylibWindow::Shutdown()
    {
        // Solo cerramos si realmente había una ventana abierta
        if (::IsWindowReady())
        {
            if (renderer) renderer->Shutdown(); // Apagamos los gráficos primero
        }
    }

    void RaylibWindow::OnUpdate()
    {
        if (WindowShouldClose())
        {
            if (eventCallback)
            {
                WindowCloseEvent event;
                eventCallback(event);
            }
        }
        if (IsWindowResized())
        {
            data.size.x = ::GetScreenWidth();
            data.size.y = ::GetScreenHeight();

            if (eventCallback)
            {
                WindowResizeEvent event(data.size.x, data.size.y);
                eventCallback(event);
            }
        }
        if (eventCallback)
        {
            if (::IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                MouseButtonPressedEvent event(MouseButton::Left);
                eventCallback(event);
            }
            if (::IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                MouseButtonReleasedEvent event(MouseButton::Left);
                eventCallback(event);
            }
        }
    }

    bool RaylibWindow::WindowShouldClose() const
    {
        return ::WindowShouldClose();
    }

    void RaylibWindow::SetTitle(const std::string& title)
    {
        ::SetWindowTitle(std::string(title).c_str());
    }

    void RaylibWindow::SetTargetFPS(int fps)
    {
        ::SetTargetFPS(fps);
    }

    void RaylibWindow::SetFullscreen(bool fullscreen)
    {
        // Si el estado actual es distinto al deseado, lo cambiamos
        if (fullscreen != ::IsWindowFullscreen())
        {
            ::ToggleFullscreen();
        }
    }

    bool RaylibWindow::IsFullscreen() const
    {
        return ::IsWindowFullscreen();
    }

    void RaylibWindow::SetVSync(bool vsync)
    {
        if (vsync)
        {
            ::SetWindowState(FLAG_VSYNC_HINT);
        }
        else
        {
            ::ClearWindowState(FLAG_VSYNC_HINT);
        }
    }
}