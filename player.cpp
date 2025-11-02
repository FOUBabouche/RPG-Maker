#include "player.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>

Player::Player()
{
	texture = new sf::Texture("res/Game/Player.png");
}

Player::~Player()
{
	delete texture;
}

void Player::setPosition(sf::Vector2f position_)
{
	position = position_;
}

void Player::setSize(sf::Vector2f size_)
{
	size = size_;
}	

sf::Vector2f Player::getPosition(void) const
{
	return position;
}

sf::Vector2f Player::getSize(void) const
{
	return size;
}

void Player::Update(float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) direction.y = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.y = 1;
	else direction.y = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction.x = 1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) direction.x = -1;
	else direction.x = 0;

	if (direction != sf::Vector2f({0.f, 0.f})) {
		position += direction.normalized() * 100.f * dt;
	}


}

void Player::Draw(sf::RenderTarget& target)
{
	sf::RectangleShape shape({ 48, 48 });
	shape.setPosition(position);
	shape.setTexture(texture);
	shape.setTextureRect({ {0, 0}, {48, 48} });
	target.draw(shape);
}
