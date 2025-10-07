#ifndef GRID_H
#define GRID_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>

class Grid {
public:
	Grid() = default;
	Grid(sf::Vector2f size, sf::Vector2f tileSize);

	void setTile(sf::Vector2f position);
	
};

#endif