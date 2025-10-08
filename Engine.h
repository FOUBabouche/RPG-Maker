#ifndef ENGINE_H
#define ENGINE_H

#include "grid.h"

#include <SFML/Window/Event.hpp>

class Engine {
public:
	void Start();
	void Event(std::optional<sf::Event> event);
	void Render(sf::RenderWindow& window);
private:
	Grid grid{ {16, 16} };
};

#endif