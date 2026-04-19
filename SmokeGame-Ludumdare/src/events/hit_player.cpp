#include "events/hit_player.h"

HitPlayer::HitPlayer(Engine::Node* enemy,HitType type): enemy(enemy),type(type)
{
}

Engine::Node* HitPlayer::GetEnemy()
{
	return enemy;
}

HitType HitPlayer::GetType()
{
	return type;
}

const char* HitPlayer::GetName() const
{
	return "HitPlayer";
}
