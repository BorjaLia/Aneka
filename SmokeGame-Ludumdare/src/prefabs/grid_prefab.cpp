#include "grid_prefab.h"

#include <memory>

#include "../src/core/components/scriptComponent.h"
#include "scripts/grid_script.h"

std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> AddGrid(Engine::SceneBuilder& builder, Engine::Vector2f pos, Engine::Vector2f dist, Engine::Vector2f iter)
{
	Engine::Node* grid = builder.CreateNode("Grid");

	grid->transform->SetPosition(pos);
	std::shared_ptr<std::shared_ptr<Engine::Node* []>[]> body;

	body = std::make_unique<std::shared_ptr<Engine::Node * []>[]>(static_cast<const size_t>(iter.y));

	for (int i = 0; i < iter.y; i++)
	{
		body[i] = std::make_unique<Engine::Node * []>(static_cast<const size_t>(iter.x));

		for (int j = 0; j < iter.x; j++)
		{
			body[i][j] = builder.CreateChildNode(grid, " " + i + j);
			body[i][j]->AddComponent<Engine::ColliderComponent>(Engine::Shape(Engine::RectangleShape(dist)));
		}
	}

	grid->AddComponent < Engine::ScriptComponent>(new GridScript(body, dist, iter));

	return body;
}
