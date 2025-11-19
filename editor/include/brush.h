#ifndef __BRUSH_H__
#define __BRUSH_H__

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

struct Brush{
    sf::IntRect uv;
    sf::Color color;
    sf::Texture* texture;
};

#endif