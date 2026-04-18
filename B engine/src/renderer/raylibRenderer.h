#pragma once
#include "IRenderer.h"

namespace Engine
{

    class RaylibRenderer : public IRenderer
    {
    public:
        RaylibRenderer() = default;
        ~RaylibRenderer() override = default;

        // Implementación de la gestión de ventana
        bool Initialize() override;
        void Shutdown() override;

        float GetDeltaTime() const override;

        // Implementación del ciclo de dibujado
        void BeginFrame() override;
        void ClearScreen(const Color& color) override;
        void EndFrame() override;

        void BeginCamera(const Vector2f& targetPosition, float zoom) override;
        void EndCamera() override;

        virtual void BeginRenderToTexture(RenderTexture2D target) override;
        virtual void EndRenderToTexture() override;
        virtual void DrawRenderTexture(RenderTexture2D target, const Vector2f& position, const Color& tint) override;

        // Implementación de las primitivas
        //void DrawRectangle(const Vector2f& position, const Vector2f& size, const Color& color) override;
        //void DrawTexture(const Texture2D& texture, const Vector2f& position, const Vector2f& scale, float rotation, const Color& tint, Pivot pivot)  override;
    
        virtual void Flush(RenderLayer layer) override;
        virtual void FlushDebug(RenderLayer layer) override;

    protected:
        Texture2D LoadTexture(const char* filepath) override;
        void UnloadTexture(Texture2D texture) override;

        Engine::Font* LoadFont(const char* filepath, int baseSize) override;
        void UnloadFont(Font* font) override;

        virtual RenderTexture2D CreateRenderTexture(const Vector2i& size) override;
        virtual void UnloadRenderTexture(RenderTexture2D target) override;

        virtual Texture2D CreateWhitePixel() override;
    };

}