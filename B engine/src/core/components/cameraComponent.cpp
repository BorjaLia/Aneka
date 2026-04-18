#include "CameraComponent.h"
#include "../Node.h"
#include "TransformComponent.h"
#include <sstream>

namespace Engine
{

    // En la implementación ya no ponemos los valores por defecto (= nullptr)
    CameraComponent::CameraComponent(IInput* input, IWindow* window, float startZoom)
        : input(input),window(window), zoom(startZoom)
    {
    }

    void CameraComponent::Update(float deltaTime)
    {
        if (input == nullptr) return;

        float wheel = input->GetMouseWheel();
        if (wheel != 0.0f)
        {
            zoom += wheel * deltaTime *100;

            if (zoom < 0.1f) zoom = 0.1f;
            if (zoom > 3.0f) zoom = 3.0f;
        }
    }

    std::string CameraComponent::ToString() const
    {
        std::stringstream ss;
        ss << "CameraComponent [Zoom: " << zoom;

        if (renderTarget.has_value())
        {
            ss << " | RenderTarget: SI (" << renderTarget.value().texture.size.x << "x" << renderTarget.value().texture.size.y << ")";
        }
        else
        {
            ss << " | RenderTarget: NO (Monitor Principal)";
        }

        ss << "]";
        return ss.str();
    }

    float CameraComponent::GetZoom() const
    {
        return zoom;
    }

    void CameraComponent::SetZoom(float newZoom)
    {
        zoom = newZoom;
    }

    void CameraComponent::SetRenderTarget(const RenderTexture2D& target)
    {
        renderTarget = target;
    }

    void CameraComponent::ClearRenderTarget()
    {
        renderTarget = std::nullopt;
    }

    bool CameraComponent::HasRenderTarget() const
    {
        return renderTarget.has_value();
    }

    RenderTexture2D CameraComponent::GetRenderTarget() const
    {
        return renderTarget.value();
    }

    Vector2f CameraComponent::ScreenToWorld(const Vector2f& screenPos) const
    {
        if (!owner || !owner->transform || !window) return screenPos; // Fallback de seguridad

        // 1. Obtenemos la posición de la cámara en el mundo
        Vector2f cameraPos = owner->transform->GetPosition();

        // 2. Obtenemos el tamaño real de la pantalla
        Vector2i screenSize = window->GetSize();
        Vector2f screenCenter = { screenSize.x / 2.0f, screenSize.y / 2.0f };

        // 3. Calculamos la posición considerando el zoom y el centro
        Vector2f worldPos;
        worldPos.x = cameraPos.x + ((screenPos.x - screenCenter.x) / zoom);

        // Cuidado con el eje Y: Si en tu motor la Y del mundo crece hacia ARRIBA (estilo matemáticas)
        // pero la Y de la pantalla crece hacia ABAJO (estilo monitores), la fórmula se invierte.
        // Asumiendo que ya arreglaste tu GetMousePosition para que crezca igual que tu mundo:
        worldPos.y = cameraPos.y + ((screenPos.y + screenCenter.y) / zoom);

        return worldPos;
    }

    Vector2f CameraComponent::WorldToScreen(const Vector2f& worldPos) const
    {
        if (!owner || !owner->transform || !window) return worldPos;

        Vector2f cameraPos = owner->transform->GetPosition();
        Vector2i screenSize = window->GetSize();
        Vector2f screenCenter = { screenSize.x / 2.0f, screenSize.y / 2.0f };

        Vector2f screenPos;
        screenPos.x = screenCenter.x + ((worldPos.x - cameraPos.x) * zoom);
        screenPos.y = screenCenter.y + ((worldPos.y - cameraPos.y) * zoom);

        return screenPos;
    }
}