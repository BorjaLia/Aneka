#include "Font.h"
#include <algorithm> // Para std::max

namespace Engine
{
    Vector2f Font::MeasureText(const std::string& text, float spacing) const
    {
        if (text.empty() || glyphs.empty())
        {
            return Vector2f(0.0f, 0.0f);
        }

        float maxWidth = 0.0f;
        float currentWidth = 0.0f;
        float currentHeight = lineHeight; // Empezamos asumiendo que hay al menos 1 línea

        for (size_t i = 0; i < text.length(); ++i)
        {
            char c = text[i];

            // Si hay un salto de línea, evaluamos si esta línea fue la más ancha
            if (c == '\n')
            {
                maxWidth = std::max(maxWidth, currentWidth);
                currentWidth = 0.0f;           // Reseteamos el cursor X
                currentHeight += lineHeight;   // Bajamos una línea en Y
                continue;
            }

            const Glyph* g = GetGlyph(c);
            if (g != nullptr)
            {
                currentWidth += g->advanceX;

                // Solo sumamos el espaciado si NO es la última letra de la línea
                if (i + 1 < text.length() && text[i + 1] != '\n')
                {
                    currentWidth += spacing;
                }
            }
        }

        // Al terminar el bucle, revisamos una última vez la línea final
        maxWidth = std::max(maxWidth, currentWidth);

        return Vector2f(maxWidth, currentHeight);
    }
}