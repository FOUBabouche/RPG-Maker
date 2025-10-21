#include "eMath.h"
#include <cmath>

float distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt((a.x-b.x)*(a.x - b.x)+(a.y-b.y)* (a.y - b.y));
}
