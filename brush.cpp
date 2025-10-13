#include "brush.h"

void Brush::SetSize(unsigned int size)
{
	m_size = size;
}

void Brush::SetTexure(sf::Texture* texture)
{
	//m_currentTexture = std::make_unique<sf::Texture>(texture);
}

void Brush::SetColor(ImVec4 color)
{
	m_color = color;
}

unsigned int Brush::GetSize(void) const {
	return m_size;
}

sf::Texture* Brush::GetTexture(void) const
{
	return m_currentTexture.get();
}

ImVec4 Brush::GetColor(void) const
{
	return m_color;
}
