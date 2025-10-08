#ifndef ENGINE_H
#define ENGINE_H

#include "grid.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

class Engine {
public:
	void Start();
	void Event(std::optional<sf::Event> event);
	void Update(float dt);
	void Render(sf::RenderTexture& render);
private:
	Grid grid{ {16, 16} };
};

#endif