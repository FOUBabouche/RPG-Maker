#include "engine.h"

void Engine::Start() {
	grid.SetTile({ 10, 10 }, sf::Color::Red, nullptr);
}

void Engine::Event(std::optional<sf::Event> event) {

}

void Engine::Update(float dt) {

}

void Engine::Render(sf::RenderTexture& render) {
	grid.DrawGrid(render);
	grid.Draw(render);
}