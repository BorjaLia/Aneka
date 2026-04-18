#include "DebugTrackingComponent.h"
#include "../Node.h"
#include "../Application.h"
#include "../Debug.h" // Nuestras flamantes macros de debug

namespace Engine
{

    DebugTrackingComponent::DebugTrackingComponent()
        : lastPosition(0.0f, 0.0f), wasMoving(false)
    {
    }

    void DebugTrackingComponent::Update(float)
    {
        if (!Application::Get().IsDebugMode()){return;}

        if (owner == nullptr) return;

        Vector2f currentPos = owner->GetGlobalPosition();

        // Verificamos si la posición cambió (¡gracias a que tenemos los datos separados por componentes!)
        bool isMovingNow = (currentPos.x != lastPosition.x || currentPos.y != lastPosition.y);

        if (isMovingNow)
        {
            wasMoving = true;
        }
        else if (!isMovingNow && wasMoving)
        {
            // Se acaba de detener
            //ENGINE_LOG("===============================");
            //ENGINE_LOG("[TRACKER] Node stopped: " << owner->name);
            //ENGINE_LOG("[TRACKER] Final Pos: " << currentPos);
            //ENGINE_LOG("===============================");

            wasMoving = false;
        }
        lastPosition = currentPos;
    }

    std::string DebugTrackingComponent::ToString() const
    {
        return "DebugTrackingComponent [WasMoving: " + std::string(wasMoving ? "True" : "False") + "]";
    }

}