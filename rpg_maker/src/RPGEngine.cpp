#include <RPGEngine.h>
#include <export/exportObject.h>
#include <camera.h>
#include <tilemap.h>

#include <SFML/Graphics/RectangleShape.hpp>

#include <windows.h>

typedef Object* (*CreateFunc)();

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
    // Exemple de load entity
    ObjectExporter::Export("Player");
    if(HMODULE lib = LoadLibraryA(".\\Project\\export\\dlls\\Debug\\Player.dll")){
        if(CreateFunc create = (CreateFunc)GetProcAddress(lib, "CreateObject"))
        {
            getCurrentScene()->addWildObject(create());
        }
    }
    //////////////////////////////////////
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
