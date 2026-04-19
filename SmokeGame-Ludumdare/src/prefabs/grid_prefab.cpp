#include "grid_prefab.h"

#include <memory>

std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> AddGrid(Engine::SceneBuilder& builder, Engine::Vector2f pos, Engine::Vector2f dist, Engine::Vector2f iter)
{
	Engine::Node* grid = builder.CreateNode("Grid");

	grid->transform->SetPosition(pos);
	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> body;

	body = std::make_unique<std::shared_ptr<Engine::Node * []>[]>(iter.y);

	for (int i = 0; i < iter.y; i++)
	{
		body[i] = std::make_unique<Engine::Node * []>(iter.x);

		for (int j = 0; j < iter.x; j++)
		{
			body[i][j] = builder.CreateChildNode(grid, " " + i + j);
			body[i][j]->transform->SetPosition(pos + Engine::Vector2f(dist.x * i, dist.y * j));
			body[i][j]->AddComponent<Engine::ColliderComponent>(Engine::Shape(Engine::RectangleShape(dist)));
		}
	}

	return body;
}
