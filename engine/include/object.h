#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <windows.h>

#include <concepts>
#include <string>

class Object
{
    public:
        Object() = default;
        Object(std::string _name) : name(_name){};
        Object(Object& b){
            name = b.name;
            position = b.position;
            size = b.size;
        }
        Object(const Object& b){
            name = b.name;
            position = b.position;
            size = b.size;
        }
        ~Object() = default;

        virtual void start() = 0;
        virtual void update(float dt) = 0;
        virtual void draw(sf::RenderTarget& target) = 0;

    public:
        Object& operator=(Object& b){
            name = b.name;
            position = b.position;
            size = b.size;
            return *this;
        }
        Object& operator=(const Object& b){
            name = b.name;
            position = b.position;
            size = b.size;
            return *this;
        }
    public:
        std::string name;
        sf::Vector2f position;
        sf::Vector2f size;
};

#endif