#include <RPGEngine.h>
#include <SFML/Graphics/RectangleShape.hpp>

void RPGEngine::start()
{
}

void RPGEngine::update(float dt)
{
}

void RPGEngine::render(sf::RenderTarget &target)
{
    sf::RectangleShape shape({100, 100});
    target.draw(shape);
}
