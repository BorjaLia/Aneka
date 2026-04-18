#include "AnimatedSpriteComponent.h"
#include "../Node.h"
#include "TransformComponent.h"
#include "../../renderer/IRenderer.h"
#include "../Application.h"
#include "../Events/AnimationEvents.h"

#include "../debug.h"

namespace Engine
{
    AnimatedSpriteComponent::AnimatedSpriteComponent(const Texture2D& texture, Pivot pivot, Color tint, RenderLayer layer)
        : texture(texture), pivot(pivot), tint(tint), layer(layer)
    {
    }

    void AnimatedSpriteComponent::AddAnimation(const std::string& name, const Animation& animation)
    {
        animations[name] = animation;
    }

    void AnimatedSpriteComponent::AddAnimationGrid(const std::string& name, int startCol, int startRow, int frameCount, float frameWidth, float frameHeight, float duration, bool looping)
    {
        Animation anim;
        anim.frameDuration = duration;
        anim.isLooping = looping;

        // Calculamos los rectángulos en base a su posición en la cuadrícula
        for (int i = 0; i < frameCount; ++i)
        {
            float x = (startCol + i) * frameWidth;
            float y = startRow * frameHeight;
            Engine::Rect rec;
            rec.pos = {x,y};
            rec.size = {frameWidth,frameHeight};
            anim.frames.push_back(rec);
        }

        animations[name] = anim;
    }

    void AnimatedSpriteComponent::Play(const std::string& name)
    {
        // Si la animación no existe, ignoramos
        if (animations.find(name) == animations.end()) { ENGINE_WARN("animation " << name << " not found!"); return; }

        // Si ya está sonando esta animación, no la reiniciamos
        if (currentAnimation == name && isPlaying) return;

        currentAnimation = name;
        currentFrameIndex = 0;
        frameTimer = 0.0f;
        isPlaying = true;
    }

    void AnimatedSpriteComponent::Stop()
    {
        isPlaying = false;
        currentFrameIndex = 0;
        frameTimer = 0.0f;
    }

    void AnimatedSpriteComponent::Pause()
    {
        isPlaying = false;
    }

    void AnimatedSpriteComponent::Resume()
    {
        if (!currentAnimation.empty())
        {
            isPlaying = true;
        }
    }

    void AnimatedSpriteComponent::Update(float deltaTime)
    {
        if (!isPlaying || currentAnimation.empty()) return;

        auto it = animations.find(currentAnimation);
        if (it == animations.end()) return;

        const Animation& anim = it->second;

        // Si la animación no tiene cuadros, abortamos
        if (anim.frames.empty()) return;

        // Acumulamos el tiempo
        frameTimer += (deltaTime * speedMultiplier);

        // Avanzamos los frames necesarios según el tiempo transcurrido
        while (frameTimer >= anim.frameDuration)
        {
            frameTimer -= anim.frameDuration;
            currentFrameIndex++;

            if (currentFrameIndex >= anim.frames.size())
            {
                if (anim.isLooping)
                {
                    currentFrameIndex = 0;
                }
                else
                {
                    // Lo dejamos en el último frame y paramos la reproducción
                    currentFrameIndex = static_cast<int>(anim.frames.size()) - 1;
                    isPlaying = false;

                    AnimationFinishedEvent event(currentAnimation, owner);
                    Application::Get().GetEventBus().Publish(event);

                    break;
                }
            }
        }
    }

    void AnimatedSpriteComponent::Draw(IRenderer* renderer)
    {
        if (owner == nullptr || owner->transform == nullptr || renderer == nullptr) return;
        if (currentAnimation.empty() || animations.find(currentAnimation) == animations.end()) return;

        const Animation& anim = animations[currentAnimation];
        if (anim.frames.empty() || currentFrameIndex >= anim.frames.size()) return;

        Vector2f position = owner->GetGlobalPosition();
        float    rotation = owner->transform->GetRotation();
        Vector2f scale = owner->transform->GetScale();

        // Obtenemos el recorte del frame actual
        Rect sourceRect = anim.frames[currentFrameIndex];

        if (targetSize.x != 0.0f && targetSize.y != 0.0f)
        {
            scale.x *= (targetSize.x / texture.size.x);
            scale.y *= (targetSize.y / texture.size.y);
        }

        // Llamamos a tu nueva sobrecarga maestra de Spritesheets
        renderer->SubmitSprite(layer, texture, sourceRect, position, rotation, scale, pivot, tint, flipX, flipY);
    }

    Vector2f AnimatedSpriteComponent::GetCurrentFrameSize() const
    {
        // 1. Si hay una animación activa, devolvemos el tamaño de su cuadro actual
        if (!currentAnimation.empty() && animations.find(currentAnimation) != animations.end())
        {
            const auto& frames = animations.at(currentAnimation).frames;
            if (!frames.empty() && currentFrameIndex < frames.size())
            {
                return { frames[currentFrameIndex].size.x, frames[currentFrameIndex].size.y };
            }
        }
        // 2. Si no hay nada reproduciéndose aún, devolvemos el tamaño del primer cuadro de la primera animación cargada
        else if (!animations.empty())
        {
            const auto& frames = animations.begin()->second.frames;
            if (!frames.empty())
            {
                return { frames[0].size.x, frames[0].size.y };
            }
        }

        // 3. Fallback absoluto
        return { static_cast<float>(texture.size.x), static_cast<float>(texture.size.y) };
    }
}