#include "tile.h"

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture)
{
	m_position = position;
	m_size = size;
	if(texture)
		m_texture = std::make_unique<sf::Texture>(*texture);
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color, sf::Texture* texture)
{
	m_position = position;
	m_size = size;
	m_color = color;
	if(texture)
		m_texture = std::make_unique<sf::Texture>(*texture);
}

Tile::Tile(Tile& tile)
{
	m_position = tile.m_position;
	m_size = tile.m_size;
	m_color = tile.m_color;
	m_texture = std::move(tile.m_texture);
}

sf::Vector2u Tile::GetPosition()
{
	return m_position;
}

sf::Vector2u Tile::GetSize()
{
	return m_size;
}

sf::Texture* Tile::getTexture()
{
	return m_texture.get();
}

sf::Color Tile::getColor()
{
	return m_color;
}
