#include "events/hit_player.h"

HitPlayer::HitPlayer(Engine::Node* enemy)
{
	this->enemy = enemy;
}

Engine::Node* HitPlayer::GetEnemy()
{
	return enemy;
}

const char* HitPlayer::GetName() const
{
	return "HitPlayer";
}
