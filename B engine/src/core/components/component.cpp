#include "../component.h"
#include "../Application.h" // Ajusta la ruta a donde esté tu Application.h
#include "../debug.h"

namespace Engine
{
    void Component::Destroy()
    {
        pendingDestruction = true;
        isActive = false; // Lo apagamos instantáneamente

        // ¡Aquí ya podemos usar Application sin miedo a dependencias circulares!
        Application::Get().MarkSceneDirty();

        
        if (!Application::Get().IsDebugMode()) { return; }
        
        ENGINE_LOG("DELETED COMPONENT");
    }
}