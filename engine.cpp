#include "engine.h"
#include "camera.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Engine::Start() {
	
}

void Engine::Event(std::optional<sf::Event> event) {
	
}

void Engine::Update(float dt) {

}

void Engine::Render(sf::RenderTexture& render, Camera& camera) {
	for (auto& grid : grids)
	{
		grid.Draw(render, camera.GetZoom());
		grid.DrawGrid(render, (sf::Vector2f)render.getSize(), camera.GetView().getCenter() - ((sf::Vector2f)render.getSize() / 2.f), camera.GetZoom());
	}
}

void Engine::AddLayer(sf::Vector2u gridSize)
{
	grids.push_back(Grid(gridSize));
}
