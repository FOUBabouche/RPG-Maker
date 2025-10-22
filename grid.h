#ifndef GRID_H
#define GRID_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>

#include "tile.h"
#include "camera.h"

class Grid {
public:
	Grid() = default;
	Grid(sf::Vector2u tileSize);

	void SetTile(sf::Vector2u position, sf::Color color, sf::Texture* texture, sf::IntRect uvSize);
	void RemoveTile(sf::Vector2u position);

	sf::Vector2u GetCoordToGridPos(sf::Vector2f mousePos);
	bool FindAt(sf::Vector2u position);

	void Draw(sf::RenderTarget& window, float zoom);
	void DrawGrid(sf::RenderTarget& window, sf::Vector2f cameraSize, sf::Vector2f cameraPos, float zoom);
private:
	std::vector<std::vector<Tile>> m_tiles;
	sf::Vector2u m_tileSize;

};

#endif