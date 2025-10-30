#include "tile.h"

#include <iostream>

Tile::Tile()
{
	m_position = {(unsigned int) - 1, (unsigned int)-1};
	m_size = { (unsigned int)-1, (unsigned int)-1};
	m_color = sf::Color::White;
	m_texture = nullptr;
}

Tile::Tile(sf::Texture* texture, sf::IntRect uv)
{
	m_position = { (unsigned int)-1, (unsigned int)-1 };
	m_size = (sf::Vector2u)uv.size;
	m_color = sf::Color::White;
	m_texture = texture;
	m_uv = uv;
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, sf::IntRect uv, std::string textureName)
{
	m_position = position;
	m_size = size;
	m_color = sf::Color::White;
	m_uv = uv;
	if (texture)
		m_texture = texture;
	else m_texture = nullptr;
	m_textureName = textureName;
}

Tile::Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color, sf::Texture* texture, sf::IntRect uv, std::string textureName)
{
	m_position = position;
	m_size = size;
	m_color = color;
	m_uv = uv;
	if(texture)
		m_texture = texture;
	else m_texture = nullptr;
	m_textureName = textureName;
}

void Tile::SetUV(sf::IntRect uv)
{
	m_uv = uv;
}

void Tile::SetSize(sf::Vector2u size)
{
	m_size = size;
}

void Tile::SetTextureName(std::string& textureName)
{
	m_textureName = textureName;
}



Tile::Tile(const Tile& tile)
{
	m_position = tile.m_position;
	m_size = tile.m_size;
	m_color = tile.m_color;
	m_texture = tile.m_texture;
	m_uv = tile.m_uv;
	m_textureName = tile.m_textureName;
	m_animIndex = tile.m_animIndex;
	m_maxAnim = tile.m_maxAnim;
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

std::string Tile::getTextureName() const
{
	return m_textureName;
}

sf::Texture* Tile::getTexture()const
{
	return m_texture;
}

sf::Color Tile::getColor()const
{
	return m_color;
}

void Tile::Update(float dt, int maxAnim)
{
	m_maxAnim = maxAnim;
	return Update(dt);
}

void Tile::Update(float dt)
{
	if (m_maxAnim > 1) {
		static float totalTime = 0;
		if (totalTime >= 1) {
			m_animIndex++;
			if (m_animIndex >= m_maxAnim) {
				m_uv.position.x -= (m_animIndex-1)*m_size.x;
				m_animIndex = 0;
			}
			m_uv.position.x += (m_animIndex)*m_size.x;
			std::cout << m_uv.position.x << " " << m_animIndex << std::endl;
			totalTime = 0;
		}
		else totalTime += dt;
	}
}

Tile& Tile::operator=(const Tile& tile)
{
	m_position = tile.m_position;
	m_size = tile.m_size;
	m_color = tile.m_color;
	m_texture = tile.m_texture;
	m_uv = tile.m_uv;
	m_textureName = tile.m_textureName;
	m_animIndex = tile.m_animIndex;
	m_maxAnim = tile.m_maxAnim;
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

std::ostream& operator<<(std::ostream& os, Tile& tile)
{
	os << tile.m_position.x << "," << tile.m_position.y << ";";
	os << tile.m_size.x << "," << tile.m_size.y << ";";
	os << (int)tile.m_color.r << "," << (int)tile.m_color.g << "," << (int)tile.m_color.b << "," << (int)tile.m_color.a << ";";
	os << tile.m_uv.position.x << "," << tile.m_uv.position.y << "," << tile.m_uv.size.x << "," << tile.m_uv.size.y << ";";
	os << tile.m_textureName << ";";
	os << std::endl;
	return os;
}
