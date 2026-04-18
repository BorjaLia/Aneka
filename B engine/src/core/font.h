#pragma once
#include "types.h"
#include <unordered_map>

namespace Engine
{
    // La información matemática de una sola letra
    struct Glyph
    {
        Rect sourceRect; // Dónde está la letra en el atlas (en píxeles)
        Vector2f offset; // Cuánto desplazarla al dibujar
        float advanceX;  // Espacio hasta la siguiente letra
    };

    // Nuestra clase de Fuente, dueña de sus datos
    class Font
    {
    private:
        std::unordered_map<char, Glyph> glyphs; // El diccionario de letras
        int baseSize;                           // Tamaño con el que se generó
        float lineHeight;                       // Espacio vertical entre líneas (\n)

    public:
        Texture2D atlas; // La gran imagen con todo el abecedario

        Font() = default;
        ~Font() = default;

        // Setters para cuando el Renderer construye la fuente
        void AddGlyph(char c, const Glyph& g) { glyphs[c] = g; }
        void SetBaseSize(int size) { baseSize = size; }
        void SetLineHeight(float height) { lineHeight = height; }

        // Getters
        int GetBaseSize() const { return baseSize; }
        float GetLineHeight() const { return lineHeight; }
        const Glyph* GetGlyph(char c) const
        {
            auto it = glyphs.find(c);
            if (it != glyphs.end()) return &it->second;
            return nullptr; // O devolver un glifo de "letra no encontrada" (?)
        }

        // --- Funciones Matemáticas ---
        // Calcula el ancho y alto total de un texto sin dibujarlo
        Vector2f MeasureText(const std::string& text, float spacing) const;
    };
}