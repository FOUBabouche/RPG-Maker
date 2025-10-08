#ifndef GRID_H
#define GRID_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "tile.h"

class Grid {
public:
	Grid() = default;
	Grid(sf::Vector2u tileSize);

	void SetTile(sf::Vector2u position, sf::Color color, sf::Texture* texture);
	void RemoveTile(sf::Vector2u position);

	bool FindAt(sf::Vector2u position);

	void Draw(sf::RenderWindow& window);
	void DrawGrid(sf::RenderWindow& window);
private:
	std::vector<std::vector<std::unique_ptr<Tile>>> m_tiles;
	sf::Vector2u m_tileSize;

};

#endif