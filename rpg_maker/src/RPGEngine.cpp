#include <RPGEngine.h>
#include <export/exportObject.h>
#include <camera.h>
#include <tilemap.h>

#include <SFML/Graphics/RectangleShape.hpp>

#include <windows.h>
#include <filesystem>

void RPGEngine::initObjects()
{
    getCurrentScene()->addObject<TileMap>("TileMap");
}

void RPGEngine::initPluginObject(){
    for(auto file : std::filesystem::directory_iterator("./Project/export/dlls/Debug")){
        if(file.path().extension() == ".dll"){
            HMODULE plugin = LoadLibraryA(file.path().string().c_str());
            ObjectPlugin objPlugin = {
                plugin,
                (CreateFunc)GetProcAddress(plugin, "CreateObject"),
                (DeleteFunc)GetProcAddress(plugin, "DestroyObject"),
                (GetNameFunc)GetProcAddress(plugin, "GetNameObject"),
                (StartFunc)GetProcAddress(plugin, "StartObject"),
                (UpdateFunc)GetProcAddress(plugin, "UpdateObject"),
                (DrawFunc)GetProcAddress(plugin, "DrawObject")
            };
            if(objPlugin.createObject == nullptr){
                FreeLibrary(plugin);
                continue;
            }
            getCurrentScene()->addObjectPlugin(objPlugin);
            getCurrentScene()->addWildObject(objPlugin.createObject());
        }
    }
}

void RPGEngine::start()
{
    addScene("First Scene");
    setCurrentScene("First Scene");
    getCurrentScene()->addlayer("Layer 1");
    getCurrentScene()->setCurrentLayer("Layer 1");
    ObjectExporter::Export("Player");
    initObjects();
    if(ObjectExporter::isFinish){
        initPluginObject();
    } 
    getCurrentScene()->start();
}

void RPGEngine::update(float dt)
{
    getCurrentScene()->update(dt);
}
