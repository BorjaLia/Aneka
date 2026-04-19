#include "mouse_script.h"

#include "core/debug.h"

MouseScript::MouseScript(Engine::CameraComponent* camera) : camera(camera)
{
}

void MouseScript::OnStart()
{
	input = Engine::Application::Get().GetInput();
}

void MouseScript::OnUpdate(float)
{
    if (!camera) return;

    Engine::Vector2f pos = camera->ScreenToWorld(input->GetMousePosition());
    
    pos.y *= -1;
    owner->transform->SetPosition(pos);
}
