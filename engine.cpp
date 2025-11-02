#include "engine.h"
#include "camera.h"
#include "collision.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Engine::Start() {
	
}

void Engine::Event(std::optional<sf::Event> event) {
	
}

void Engine::Update(float dt) {
	player.Update(dt);
	for (auto x : grids[0].getTiles())
	{
		for (auto y : x) {
			Collision col;
			if (col.AABB(y, player)) {
				std::cout << "Col";
			};
		}
	}
}

void Engine::Render(sf::RenderTexture& render, Camera& camera) {
	for (auto& grid : grids)
	{
		grid.Draw(render, camera.GetZoom());
		
	}
	player.Draw(render);
}

void Engine::AddLayer(sf::Vector2u gridSize)
{
	grids.push_back(Grid(gridSize));
}
