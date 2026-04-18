#pragma once
#include "../Component.h" // Subimos un nivel para encontrar Component.h
#include "../Types.h"
#include "../Math.h"

namespace Engine
{
    class SpriteComponent : public Component
    {
    private:
        bool flipX = false;
        bool flipY = false;

    public:
        Texture2D texture;
        Color tint;
        Pivot pivot;
        RenderLayer layer;

        SpriteComponent(const Texture2D& texture, Pivot pivot = Pivot::TopLeft, Color tint = { 255, 255, 255, 255 }, RenderLayer layer = RenderLayer::World);
        ~SpriteComponent() override = default;

        void Update(float deltaTime) override;
        void Draw(IRenderer* renderer) override;

        std::string ToString() const override;

        // Getters y setters por si queremos cambiar la textura o la capa en tiempo real
        void SetTexture(const Texture2D& newTexture) { texture = newTexture; }
        void SetTint(const Color& newTint) { tint = newTint; }

        void SetFlipX(bool flip) { flipX = flip; }
        void SetFlipY(bool flip) { flipY = flip; }
        bool GetFlipX() const { return flipX; }
        bool GetFlipY() const { return flipY; }

        void SetLayer(RenderLayer newLayer) { layer = newLayer; }
        RenderLayer GetLayer() const { return layer; }
    };
}