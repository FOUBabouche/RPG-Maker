#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player {
public:
	Player();
	~Player();

	void setPosition(sf::Vector2f position_);
	void setSize(sf::Vector2f size_);

	sf::Vector2f getPosition(void) const;
	sf::Vector2f getSize(void) const;

	void Update(float dt);
	void Draw(sf::RenderTarget& target);

private:
	sf::Vector2f position;
	sf::Vector2f size = { 48, 48 };
	sf::Vector2f direction;
	sf::Texture* texture;
};

#endif