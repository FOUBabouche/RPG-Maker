#include "brush.h"

void Brush::SetSize(unsigned int size)
{
	m_size = size;
}

void Brush::SetTexure(sf::Texture* texture)
{
	m_currentTexture.reset(texture);
}

void Brush::SetColor(sf::Color color)
{
	m_color = color;
}

void Brush::SetUV(sf::IntRect uv)
{
	m_uv = uv;
}

unsigned int Brush::GetSize(void) const {
	return m_size;
}

sf::Texture* Brush::GetTexture(void) const
{
	return m_currentTexture.get();
}

sf::IntRect Brush::GetUV(void) const
{
	return m_uv;
}

sf::Color Brush::GetColor(void) const
{
	return m_color;
}
