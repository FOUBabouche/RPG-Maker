#ifndef ENGINE_H
#define ENGINE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "grid.h"
#include "camera.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <vector>

class Engine {
public:
	void Start();
	void Event(std::optional<sf::Event> event);
	void Update(float dt);
	void Render(sf::RenderTexture& render, Camera& camera);

	void AddLayer(sf::Vector2u gridSize);
public:
	std::vector<Grid> grids;
};

#endif