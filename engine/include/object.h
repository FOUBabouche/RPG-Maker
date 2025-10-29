#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/System/Vector2.hpp>
#include <string>

struct Object
{
    std::string name;
    sf::Vector2f position;
    sf::Vector2f size;

    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};


#endif