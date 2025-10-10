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
	grid.Draw(render);
	grid.DrawGrid(render, camera);
}