#include "engine.h"

void Engine::Start() {
	grid.SetTile({ 10, 10 }, sf::Color::Red, nullptr);
}

void Engine::Event(std::optional<sf::Event> event) {

}

void Engine::Render(sf::RenderWindow& window) {
	grid.DrawGrid(window);
	grid.Draw(window);
}