#include <RPGEngine.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <camera.h>
#include <tilemap.h>

void RPGEngine::initObjects()
{
    getCurrentScene()->addObject(new Camera("MainCamera"));
    getCurrentScene()->addObject(new TileMap("TileMap"));
}

void RPGEngine::start()
{
    addScene("First Scene");
    setCurrentScene("First Scene");
    getCurrentScene()->addlayer("Layer 1");
    getCurrentScene()->setCurrentLayer("Layer 1");
    initObjects();
    for(auto &layer : getCurrentScene()->getLayers().getHandle()){
        for(auto& obj : layer.second)
            obj->start();
    }
}

void RPGEngine::update(float dt)
{
    for(auto &layer : getCurrentScene()->getLayers().getHandle()){
        for(auto& obj : layer.second)
            obj->update(dt);
    }
}
