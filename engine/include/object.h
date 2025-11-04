#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <string>

class Object
{
    public:
        Object() = default;
        Object(Object& b){
            name = b.name;
            position = b.position;
            size = b.size;
        }
        virtual ~Object() = default;

        virtual void Start() = 0;
        virtual void Update() = 0;
        virtual void draw(sf::RenderTarget&) = 0;

    public:
        Object& operator=(Object& b){
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