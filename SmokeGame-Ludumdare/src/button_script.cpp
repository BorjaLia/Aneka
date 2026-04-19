#include "button_script.h"

ButtonScript::ButtonScript(Engine::Texture2D texture, Engine::Vector2f size, float rotation)
{
	this->texture = texture;

	this->size = size;
	this->rotation = rotation;
}

ButtonScript::ButtonScript(Engine::Texture2D texture, Engine::Texture2D textureHover, Engine::Vector2f size, float rotation)
{
	this->texture = texture;
	this->textureHover = textureHover;

	this->size = size;
	this->rotation = rotation;
}

void ButtonScript::OnStart()
{
	button = owner->GetComponent<Engine::ButtonComponent>();
	sprite = owner->GetComponent<Engine::SpriteComponent>();

	owner->transform->SetScale(size);
	button->Start();
}

void ButtonScript::OnUpdate(float)
{
	auto* rm = Engine::Application::Get().GetResourceManager();

	if (button->IsHovered())
	{
		sprite->SetTexture(rm->GetTexture("res/sprites/hoveredButton.png"));
		owner->transform->SetRotation(rotation);
		owner->FindChild("ButtonText")->transform->SetRotation(15);
	}
	else
	{
		sprite->SetTexture(rm->GetTexture("res/sprites/button.png"));
		owner->transform->SetRotation(0);
		owner->FindChild("ButtonText")->transform->SetRotation(0);
	}
}
