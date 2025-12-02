#include "Player.h"
#include <iostream>

void Player::start(){
    name = "Player";
    position = {};
    std::cout << "Player init" << std::endl;
}
void Player::update(float dt){
    std::cout << "Test" << std::endl;
}
void Player::draw(sf::RenderTarget& target){
    shape.setSize({100, 100});
    shape.setPosition({50, 50});
    target.draw(shape);
}