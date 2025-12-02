#ifndef __Player_H__
#define __Player_H__

#include <object.h>
#include <SFML/Graphics/RectangleShape.hpp>

class Player : public Object{
  public:
    Player() = default;
    Player(std::string _name) { name = _name;};
    ~Player() = default;

    void start() override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;
  private:
    sf::RectangleShape shape;
};
#endif