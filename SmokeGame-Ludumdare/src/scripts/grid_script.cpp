#include "grid_script.h"

void GridScript::OnStart()
{
	for (int i = 0; i < iter.x; i++)
	{
		for (int j = 0; j < iter.y; j++)
		{
			body[i][j]->transform->SetPosition(Engine::Vector2f(dist.x * i, dist.y * j));
		}
	}
}

GridScript::GridScript(std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> body, Engine::Vector2f dist, Engine::Vector2f iter)
{
	this->body = body;
	this->dist = dist;
	this->iter = iter;
}
