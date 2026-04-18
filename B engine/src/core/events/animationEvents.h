#pragma once
#include "Event.h"
#include <string>

namespace Engine
{
    class Node; // Declaración adelantada para no incluir Node.h aquí

    class AnimationFinishedEvent : public EventBase<AnimationFinishedEvent>
    {
    private:
        std::string animationName;
        Node* ownerNode;

    public:
        AnimationFinishedEvent(const std::string& name, Node* owner)
            : animationName(name), ownerNode(owner)
        {
        }

        std::string GetAnimationName() const { return animationName; }
        Node* GetNode() const { return ownerNode; }

        const char* GetName() const override { return "AnimationFinishedEvent"; }
    };
}