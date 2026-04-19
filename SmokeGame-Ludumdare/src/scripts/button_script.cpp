#include "button_script.h"

ButtonScript::ButtonScript(Engine::Texture2D texture, Engine::Vector2f size, float rotation, Engine::AudioClip audio)
{
	this->texture = texture;

	this->size = size;
	this->rotation = rotation;

	this->audio = audio;
}

ButtonScript::ButtonScript(Engine::Texture2D texture, Engine::Texture2D textureHover, Engine::Vector2f size, float rotation, Engine::AudioClip audio)
{
	this->texture = texture;
	this->textureHover = textureHover;

	this->size = size;
	this->rotation = rotation;

	this->audio = audio;
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
		sprite->SetTexture(textureHover);
		owner->transform->SetRotation(rotation);
		owner->FindChild("ButtonText")->transform->SetRotation(15);
		Engine::AudioComponent* audioComp = owner->GetComponent<Engine::AudioComponent>();

		Engine::AudioPlayParams params = audioComp->GetParams();
		params.volume = 0.3f;
		audioComp->SetParams(params);

		if (!Engine::Application::Get().GetAudio()->IsPlaying(audio) && !playedHoveredSound)
		{
			audioComp->Play();
			playedHoveredSound = true;
		}
	}
	else
	{
		sprite->SetTexture(texture);
		owner->transform->SetRotation(0);
		owner->FindChild("ButtonText")->transform->SetRotation(0);
		playedHoveredSound = false;
	}
}
