#include "events/hit_player.h"

HitPlayer::HitPlayer(Engine::Node* enemy, HitType type): type(type)
{
}

Engine::Node* HitPlayer::GetEnemy()
{
	return enemy;
}

HitType HitPlayer::GetHitType()
{
	return type;
}

const char* HitPlayer::GetName() const
{
	return "HitPlayer";
}
