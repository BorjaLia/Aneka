#include "SpriteComponent.h"
#include "../Node.h"
#include "TransformComponent.h"
#include "../../Renderer/IRenderer.h"

namespace Engine
{
    SpriteComponent::SpriteComponent(const Texture2D& texture, Pivot pivot, Color tint, RenderLayer layer)
        : texture(texture), pivot(pivot), tint(tint), layer(layer)
    {
    }

    void SpriteComponent::Update(float /*deltaTime*/) {}

    void SpriteComponent::Draw(IRenderer* renderer)
    {
        if (owner == nullptr || owner->transform == nullptr || renderer == nullptr) return;

        // Use global position so sprites on child nodes render in the correct world location.
        // Local position would only be correct for root-level nodes.
        Vector2f position = owner->GetGlobalPosition();
        float    rotation = owner->transform->GetRotation();
        Vector2f scale    = owner->transform->GetScale();

        renderer->SubmitSprite(layer, texture, position, rotation, scale, pivot, tint, flipX, flipY);
    }

    std::string SpriteComponent::ToString() const
    {
        std::stringstream ss;
        ss << "SpriteComponent [Color: " << tint << "]";
        return ss.str();
    }
}
