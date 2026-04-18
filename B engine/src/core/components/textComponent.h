#pragma once
#include "../Component.h"
#include "../Types.h"
#include "../font.h"
#include <string>

namespace Engine
{
    enum class TextAlignment
    {
        Left,
        Center,
        Right
    };

    class TextComponent : public Component
    {
    public:
        // Datos Básicos
        std::string text;
        Font* font;

        // Estilo Visual
        float fontSize;
        Color tint;
        float extraLetterSpacing;
        float extraLineSpacing;

        // Layout
        TextAlignment alignment;
        Pivot pivot;
        RenderLayer layer;

        TextComponent(Font* font = nullptr, const std::string& text = "",
            float fontSize = 32.0f, Color tint = { 255, 255, 255, 255 },
            RenderLayer layer = RenderLayer::UI);

        ~TextComponent() override = default;

        void Update(float deltaTime) override;
        void Draw(IRenderer* renderer) override;
        std::string ToString() const override;

        // Devuelve el tamaño real del texto escalado en pantalla
        Vector2f GetBounds() const;

        // Getters/Setters útiles
        void SetText(const std::string& newText) { text = newText; }
        void SetFont(Font* newFont) { font = newFont; }
    };
}