#ifndef __BASE_EDITOR_H__
#define __BASE_EDITOR_H__

#include <SFML/Graphics/RenderTarget.hpp>

class Base_Editor{
    public:
        virtual void start() = 0;
        virtual void update(float dt) = 0;
        virtual void draw() = 0;
};

#endif