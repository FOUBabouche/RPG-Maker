#ifndef BRUSH_H
#define BRUSH_H

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

class Brush {
public:
	Brush() = default;

	void SetSize(unsigned int size);
	void SetTexure(sf::Texture* texture);
	void SetColor(sf::Color color);

	unsigned int GetSize(void) const;
	sf::Texture* GetTexture(void) const;
	sf::Color GetColor(void);

	virtual void click() {};
protected:
	unsigned int m_size;
	std::unique_ptr<sf::Texture> m_currentTexture;
	sf::Color m_color = sf::Color::White;
};

#endif