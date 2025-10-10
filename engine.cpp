#include "engine.h"
#include "camera.h"

#include <SFML/Graphics/RectangleShape.hpp>

void Engine::Start() {
	sf::Texture placeHolder("Placeholder.png");
	grid.SetTile({ 0, 0 }, sf::Color::Red, &placeHolder);
	grid.SetTile({ 10, 10 }, sf::Color::Red, &placeHolder);
}

void Engine::Event(std::optional<sf::Event> event) {
	
}

void Engine::Update(float dt) {

}

void Engine::Render(sf::RenderTexture& render, Camera& camera) {
	grid.DrawGrid(render, camera);
	grid.Draw(render);
}