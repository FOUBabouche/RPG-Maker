#include "tile.h"

Tile::Tile()
{
	m_position = {0, 0};
	m_size = {16, 16};
	m_color = sf::Color::White;
	m_texture = nullptr;
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture)
{
	m_position = position;
	m_size = size;
	m_color = sf::Color::White;
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
	m_texture.reset(tile.m_texture.get());
}

sf::Vector2u Tile::GetPosition()const
{
	return m_position;
}

sf::Vector2u Tile::GetSize()const
{
	return m_size;
}

sf::Texture* Tile::getTexture()const
{
	return m_texture.get();
}

sf::Color Tile::getColor()const
{
	return m_color;
}
