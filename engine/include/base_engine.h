#ifndef __BASE_ENGINE_H__
#define __BASE_ENGINE_H__

#include <SFML/Graphics/RenderTarget.hpp>

class BaseEngine{
    public:
        BaseEngine() =default;
        virtual ~BaseEngine() = default;

        virtual void start()=0;
        virtual void update(float dt)=0;
        virtual void render(sf::RenderTarget& target)=0;
    
};

#endif