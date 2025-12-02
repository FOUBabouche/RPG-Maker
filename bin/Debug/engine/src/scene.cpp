#include <scene.h>
#include <camera.h>

#include <iostream>
#include <typeindex>

Scene::Scene(std::string name)
{
    m_name = name;
}

Scene::~Scene()
{
    layers.clear();
}

std::string Scene::getName(void) const
{
    return m_name;
}

Layers &Scene::getLayers(void)
{
    return layers;
}

void Scene::setCurrentLayer(const std::string layerName)
{
    currentLayerName = layerName;
}

std::string Scene::getCurrentLayerName(void) const
{
    return currentLayerName;
}

std::vector<Object *> Scene::getCurrentLayer(void)
{
    return layers[currentLayerName];
}

void Scene::addlayer(std::string layerName)
{
    layers.addLayer(layerName);
}

void Scene::start()
{
    for (auto layer : layers.getHandle())
        for (auto &obj : layer.second)
            if(obj->isScripted){
                for(auto &objPlug : objPlugins)
                    if(objPlug.getNameObject(obj) == obj->name){
                        objPlug.startObject(obj);
                        break;
                    }
            }
            else 
                obj->start();
}

void Scene::update(float dt)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
                if(typeid(obj) != typeid(Camera))
                    if(obj->isScripted){
                        for(auto objPlug : objPlugins)
                            if(objPlug.getNameObject(obj) == obj->name){
                                objPlug.updateObject(obj, dt);
                                break;
                            }
                    }
                    else 
                        obj->update(dt);
}

void Scene::render(sf::RenderTarget &target)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
            if(typeid(*obj).name() != typeid(Camera).name()){
                if(obj->isScripted){
                        for(auto objPlug : objPlugins)
                            if(objPlug.getNameObject(obj) == obj->name){
                                objPlug.drawObject(obj, target);
                                break;
                            }
                    }
                    else 
                        obj->draw(target);
            }
}
