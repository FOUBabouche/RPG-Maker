#ifndef TILE_H
#define TILE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory>

class Tile
{
public:
	Tile() = default;
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture);
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color,sf::Texture* texture);
	Tile(Tile& tile);

	sf::Vector2u GetPosition();
	sf::Vector2u GetSize();

	sf::Texture* getTexture();
	sf::Color getColor();

private:
	sf::Vector2u m_position;
	sf::Vector2u m_size;
	sf::Color m_color;
	std::unique_ptr<sf::Texture> m_texture;
};

#endif