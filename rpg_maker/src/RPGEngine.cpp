#include <RPGEngine.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <camera.h>
#include <tilemap.h>

void RPGEngine::initObjects()
{
    addObject(new Camera("MainCamera"));
    addObject(new TileMap("TileMap"));
}

void RPGEngine::start()
{
    initObjects();
    for(auto& obj : m_objects)
        obj->start();
}

void RPGEngine::update(float dt)
{
    for(auto& obj : m_objects)
        obj->update(dt);
}
