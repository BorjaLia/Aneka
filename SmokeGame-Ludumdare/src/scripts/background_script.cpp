#include "background_script.h"

void BackgroundScript::OnStart() 
{
	backgroundFar = owner->FindChild("backgroundFar");
	clouds = owner->FindChild("clouds");
	mountainNear = owner->FindChild("mountainNear");
	mountainFar = owner->FindChild("mountainFar");
}

void BackgroundScript::OnUpdate(float deltaTime) 
{
	Engine::Vector2f pos = clouds->transform->GetPosition();
	pos -= Engine::Vector2f(parallax_speed_mid * deltaTime, 0.0f);
	clouds->transform->SetPosition(pos);

	if (clouds->transform->GetPosition().x <= -clouds->GetComponent<Engine::SpriteComponent>()->texture.size.x) clouds->transform->SetPosition(Engine::Vector2f(0.0f, 0.0f));

	pos = mountainNear->transform->GetPosition();
	pos -= Engine::Vector2f(parallax_speed_mid_front * deltaTime, 0.0f);
	mountainNear->transform->SetPosition(pos);

	if (mountainNear->transform->GetPosition().x <= -mountainNear->GetComponent<Engine::SpriteComponent>()->texture.size.x) mountainNear->transform->SetPosition(Engine::Vector2f(0.0f, 0.0f));

	pos = mountainFar->transform->GetPosition();
	pos -= Engine::Vector2f(parallax_speed_front * deltaTime, 0.0f);
	mountainFar->transform->SetPosition(pos);

	if (mountainFar->transform->GetPosition().x <= -mountainFar->GetComponent<Engine::SpriteComponent>()->texture.size.x) mountainFar->transform->SetPosition(Engine::Vector2f(0.0f, 0.0f));
}
