#include "scriptComponent.h"

namespace Engine
{
	ScriptComponent::ScriptComponent(Script* userScript) : script(userScript) {}

    ScriptComponent::~ScriptComponent()
    {
        if (script) script->OnDestroy();
    }

    void ScriptComponent::Initialize() 
    {
        // ¡Magia arquitectónica! 
        // Como AddComponent ya seteó nuestro 'owner', se lo pasamos al script del usuario.
        if (script && owner)
        {
            script->SetOwner(owner);
        }
    }

    void ScriptComponent::Start() 
    {
        if (script) script->OnStart();
    }

    void ScriptComponent::Update(float deltaTime) 
    {
        if (script) script->OnUpdate(deltaTime);
    }

    void ScriptComponent::FixedUpdate(float fixedDeltaTime) 
    {
        if (script) script->OnFixedUpdate(fixedDeltaTime);
    }

    template <typename T>
    T* ScriptComponent::GetScript() const
    {
        return dynamic_cast<T*>(script.get());
    }

}