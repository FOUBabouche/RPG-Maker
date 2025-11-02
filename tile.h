#ifndef TILE_H
#define TILE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <memory>
#include <iostream>

class Tile
{
public:
	Tile();
	Tile(const Tile& tile);
	~Tile() = default;
	Tile(sf::Texture* texture, sf::IntRect uv);
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Texture* texture, sf::IntRect uvSize, std::string textureName);
	Tile(sf::Vector2u position, sf::Vector2u size, sf::Color color,sf::Texture* texture, sf::IntRect uvSize, std::string textureName);

	void SetUV(sf::IntRect uv);
	void SetSize(sf::Vector2u size);
	void SetTextureName(std::string& textureName);

	sf::Vector2u GetPosition() const;
	sf::Vector2u GetSize() const;
	sf::IntRect getUV() const;
	std::string getTextureName() const;
	sf::Texture* getTexture() const;
	sf::Color getColor() const;

	void Update(float dt, int maxAnim);
	void Update(float dt);

public:
	Tile& operator=(const Tile& tile);
	bool operator==(Tile& tile);
	bool operator!=(Tile& tile);

	friend std::ostream& operator<<(std::ostream& os, Tile& tile);
	int m_maxAnim;
private:
	sf::Vector2u m_position;
	sf::Vector2u m_size;
	sf::Color m_color;
	std::string m_textureName;
	sf::Texture* m_texture = nullptr;
	sf::IntRect m_uv;

	int m_animIndex = 0;
};

using NoTile = Tile;

#endif