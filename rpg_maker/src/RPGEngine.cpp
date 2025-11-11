#include <RPGEngine.h>
#include <SFML/Graphics/RectangleShape.hpp>

void RPGEngine::start()
{
    for(auto& obj : m_objects)
        obj->start();
}

void RPGEngine::update(float dt)
{
    for(auto& obj : m_objects)
        obj->update(dt);
}
