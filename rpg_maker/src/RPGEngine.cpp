// Engine
#include <RPGEngine.h>
#include <camera.h>
#include <tilemap.h>

// Scripting API


// SFML
#include <SFML/Graphics/RectangleShape.hpp>

// STL
#include <windows.h>
#include <filesystem>

void RPGEngine::initObjects()
{
    getCurrentScene()->addObject<TileMap>("TileMap");
}

void RPGEngine::start()
{
    
    addScene("First Scene");
    setCurrentScene("First Scene");
    getCurrentScene()->addlayer("Layer 1");
    getCurrentScene()->setCurrentLayer("Layer 1");
    initObjects();
    getCurrentScene()->start();
}

void RPGEngine::update(float dt)
{
    getCurrentScene()->update(dt);
}
