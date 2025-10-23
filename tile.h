#ifndef TILE_H
#define TILE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory>

class Tile
{
public:
	Tile();
	Tile(const Tile& tile);
	~Tile() = default;
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, sf::IntRect uvSize);
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color,sf::Texture* texture, sf::IntRect uvSize);

	void SetSize(sf::Vector2u size);

	sf::Vector2u GetPosition() const;
	sf::Vector2u GetSize() const;

	sf::IntRect getUV() const;
	sf::Texture* getTexture() const;
	sf::Color getColor() const;

public:
	Tile& operator=(const Tile& tile);
	bool operator==(Tile& tile);
	bool operator!=(Tile& tile);
private:
	sf::Vector2u m_position;
	sf::Vector2u m_size;
	sf::Color m_color;
	sf::Texture* m_texture = nullptr;
	sf::IntRect m_uv;
};

#endif