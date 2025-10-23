#ifndef BRUSH_H
#define BRUSH_H

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

class Brush {
public:
	Brush();
	~Brush();

	void SetSize(unsigned int size);
	void SetTexture(sf::Texture& texture);
	void SetColor(sf::Color color);
	void SetUV(sf::IntRect uv);

	unsigned int GetSize(void) const;
	sf::Texture* GetTexture(void) const;
	sf::Color GetColor(void) const;
	sf::IntRect GetUV(void) const;

	virtual void click() {};
protected:
	unsigned int m_size;
	sf::Texture* m_currentTexture;
	sf::Color m_color = sf::Color::White;
	sf::IntRect m_uv;
};

#endif