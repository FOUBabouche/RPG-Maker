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
    layers.addLayer("Layer 1");
    currentLayerName = "Layer 1";

    initObjects();
    for(auto &layer : layers.getHandle()){
        for(auto& obj : layer.second)
            obj->start();
    }
}

void RPGEngine::update(float dt)
{
    for(auto &layer : layers.getHandle()){
        for(auto& obj : layer.second)
            obj->update(dt);
    }
}
