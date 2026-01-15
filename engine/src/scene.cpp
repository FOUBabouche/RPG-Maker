#include <scene.h>
#include <camera.h>

#include <iostream>
#include <typeindex>

Scene::Scene(std::string name, PluginObjectManager* pom)
{
    m_name = name;
    _pom = pom;
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
            if(!_pom) obj->start();
            else _pom->start(obj);
}

void Scene::update(float dt)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
                if(typeid(obj) != typeid(Camera))
                    if(!_pom) obj->update(dt);
                    else _pom->update(obj, dt);
}

void Scene::render(sf::RenderTarget &target)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
            if(typeid(*obj).name() != typeid(Camera).name()){
                if(!_pom) obj->draw(target);
                    else _pom->render(obj, target);
            }
}
