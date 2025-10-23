#include "tile.h"

Tile::Tile()
{
	m_position = {(unsigned int) - 1, (unsigned int)-1};
	m_size = { (unsigned int)-1, (unsigned int)-1};
	m_color = sf::Color::White;
	m_texture = nullptr;
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, sf::IntRect uv)
{
	m_position = position;
	m_size = size;
	m_color = sf::Color::White;
	m_uv = uv;
	if(texture)
		m_texture = texture;
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color, sf::Texture* texture, sf::IntRect uv)
{
	m_position = position;
	m_size = size;
	m_color = color;
	m_uv = uv;
	if(texture)
		m_texture = texture;
}

void Tile::SetSize(sf::Vector2u size)
{
	m_size = size;
}

Tile::Tile(const Tile& tile)
{
	m_position = tile.m_position;
	m_size = tile.m_size;
	m_color = tile.m_color;
	m_texture = tile.m_texture;
	m_uv = tile.m_uv;
}

sf::Vector2u Tile::GetPosition()const
{
	return m_position;
}

sf::Vector2u Tile::GetSize()const
{
	return m_size;
}

sf::IntRect Tile::getUV() const
{
	return m_uv;
}

sf::Texture* Tile::getTexture()const
{
	return m_texture;
}

sf::Color Tile::getColor()const
{
	return m_color;
}

Tile& Tile::operator=(const Tile& tile)
{
	m_position = tile.m_position;
	m_size = tile.m_size;
	m_color = tile.m_color;
	m_texture = tile.m_texture;
	m_uv = tile.m_uv;
	return *this;
}

bool Tile::operator==(Tile& tile)
{
	return (m_position == tile.m_position &&
			m_size == tile.m_size &&
			m_color == tile.m_color &&
			m_texture == tile.m_texture &&
			m_uv == tile.m_uv);
}

bool Tile::operator!=(Tile& tile)
{
	return !(m_position == tile.m_position &&
		m_size == tile.m_size &&
		m_color == tile.m_color &&
		m_texture == tile.m_texture &&
		m_uv == tile.m_uv);
}
