#pragma once
#include "../Component.h"
#include "../../Input/IInput.h"
#include "../../Core/IWindow.h"
#include <optional>

namespace Engine
{

    class CameraComponent : public Component
    {
    private:
        bool showDebug = true;

        IInput* input;
        IWindow* window;
        float zoom;
        std::optional<RenderTexture2D> renderTarget;

    public:
        // Constructor con valores por defecto en la declaración
        CameraComponent(IInput* input = nullptr, IWindow* window = nullptr, float startZoom = 1.0f);
        ~CameraComponent() override = default;

        void Update(float deltaTime) override;

        std::string ToString() const override;

        float GetZoom() const;
        void SetZoom(float newZoom);

        void SetShowDebug(bool show) { showDebug = show; }
        bool GetShowDebug() const { return showDebug; }

        void SetRenderTarget(const RenderTexture2D& target);
        void ClearRenderTarget();
        bool HasRenderTarget() const;
        RenderTexture2D GetRenderTarget() const;
    
        Vector2f ScreenToWorld(const Vector2f& screenPos) const;
        Vector2f WorldToScreen(const Vector2f& worldPos) const;
    };

}