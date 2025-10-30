#ifndef BRUSH_H
#define BRUSH_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

#include <iostream>
#include <memory>

class Brush {
public:
	Brush() = default;
	~Brush() = default;

	void SetSize(unsigned int size);
	void SetTextureName(std::string textureName);
	void SetTexture(sf::Texture* texture);
	void SetColor(sf::Color color);
	void SetUV(sf::IntRect uv);
	

	unsigned int GetSize(void) const;
	std::string GetTextureName(void) const;
	sf::Texture* GetTexture(void) const;
	sf::Color GetColor(void) const;
	sf::IntRect GetUV(void) const;

	virtual void click() {};
	int maxAnim = 0;
protected:
	unsigned int m_size;
	sf::Texture* m_currentTexture;
	std::string m_textureName;
	sf::Color m_color = sf::Color::White;
	sf::IntRect m_uv;
};

#endif