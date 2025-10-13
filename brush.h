#ifndef BRUSH_H
#define BRUSH_H

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <imgui.h>

class Brush {
public:
	Brush() = default;

	void SetSize(unsigned int size);
	void SetTexure(sf::Texture* texture);
	void SetColor(ImVec4 color);

	unsigned int GetSize(void) const;
	sf::Texture* GetTexture(void) const;
	ImVec4 GetColor(void) const;

	virtual void click();
protected:
	unsigned int m_size;
	std::unique_ptr<sf::Texture> m_currentTexture;
	ImVec4 m_color;
};

#endif