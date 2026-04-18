#pragma once
#include "../Component.h"
#include "../Types.h"
#include "../Events/ApplicationEvents.h"
#include <string>

namespace Engine
{
    class WindowResizeEvent;

    enum class AnchorPreset
    {
        TopLeft, TopCenter, TopRight,
        MiddleLeft, Center, MiddleRight,
        BottomLeft, BottomCenter, BottomRight,
        Custom
    };

    class UIAnchorComponent : public Component
    {
    private:
        AnchorPreset preset;
        Vector2f customAnchor;
        Vector2f offset;
        Vector2f size;

        bool isDirty;
        uint32_t resizeEventId = 0;

        Vector2f GetAnchorVector() const;
        void OnWindowResize(WindowResizeEvent& e);
        void RecalculatePosition();

    public:
        UIAnchorComponent(AnchorPreset preset = AnchorPreset::TopLeft,
            Vector2f offset = { 0.0f, 0.0f },
            Vector2f size = { 100.0f, 100.0f });
        ~UIAnchorComponent() override;

        void Start()          override;
        void Update(float dt) override;

        void SetPreset(AnchorPreset p) { preset = p;      MarkDirty(); }
        void SetCustomAnchor(const Vector2f& a) { preset = AnchorPreset::Custom; customAnchor = a; MarkDirty(); }
        void SetOffset(const Vector2f& o) { offset = o;      MarkDirty(); }
        void SetSize(const Vector2f& s) { size = s;      MarkDirty(); }

        void MarkDirty();

        Vector2f     GetSize()   const { return size; }
        Vector2f     GetOffset() const { return offset; }
        AnchorPreset GetPreset() const { return preset; }

        std::string ToString() const override;
    };
}