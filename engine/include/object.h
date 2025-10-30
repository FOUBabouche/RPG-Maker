#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>

struct Object
{
    std::string name;
    sf::Vector2f position;
    sf::Vector2f size;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw(sf::RenderTarget&) = 0;
};


#endif