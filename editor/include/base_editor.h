#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <SFML/Graphics/RenderTarget.hpp>

class Base_Editor{
    public:
        virtual void start();
        virtual void update(float dt);
        virtual void draw(sf::RenderTarget& target);
};

#endif