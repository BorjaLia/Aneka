#pragma once
#include "../Component.h"
#include "../Types.h"
#include "../Math.h"
#include <vector>
#include <unordered_map>
#include <string>

namespace Engine
{
    // Define las reglas de una animación específica
    struct Animation
    {
        std::vector<Rect> frames;
        float frameDuration = 0.1f;
        bool isLooping = true;
    };

    class AnimatedSpriteComponent : public Component
    {
    private:
        std::unordered_map<std::string, Animation> animations;

        std::string currentAnimation = "";
        int currentFrameIndex = 0;
        float frameTimer = 0.0f;
        bool isPlaying = false;

        bool flipX = false;
        bool flipY = false;

        Vector2f targetSize = { 0.0f, 0.0f };

    public:
        Texture2D texture;
        Color tint;
        Pivot pivot;
        RenderLayer layer;

        float speedMultiplier = 1.0f;

        AnimatedSpriteComponent(const Texture2D& texture, Pivot pivot = Pivot::TopLeft, Color tint = { 255, 255, 255, 255 }, RenderLayer layer = RenderLayer::World);
        ~AnimatedSpriteComponent() override = default;

        void Update(float deltaTime) override;
        void Draw(IRenderer* renderer) override;

        // --- Gestión de Animaciones ---

        // Añade una animación enviando los rectángulos manualmente
        void AddAnimation(const std::string& name, const Animation& animation);

        // Helper: Genera los cuadros automáticamente basándose en una cuadrícula
        void AddAnimationGrid(const std::string& name, int startCol, int startRow, int frameCount, float frameWidth, float frameHeight, float duration = 0.1f, bool looping = true);

        // --- Controles de Reproducción ---
        void Play(const std::string& name);
        void Stop();
        void Pause();
        void Resume();

        bool IsPlaying() const { return isPlaying; }
        std::string GetCurrentAnimation() const { return currentAnimation; }

        Vector2f GetCurrentFrameSize() const;

        // --- Propiedades Visuales ---
        void SetFlipX(bool flip) { flipX = flip; }
        void SetFlipY(bool flip) { flipY = flip; }
        bool GetFlipX() const { return flipX; }
        bool GetFlipY() const { return flipY; }
    
        void SetTargetSize(const Vector2f& size) { targetSize = size; }
        Vector2f GetTargetSize() const { return targetSize; }
    };
}