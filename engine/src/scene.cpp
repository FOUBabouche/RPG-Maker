#include <scene.h>

Scene::Scene(std::string name)
{
    m_name = name;
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
        for (auto obj : layer.second)
            obj->start();
}

void Scene::update(float dt)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
            obj->update(dt);
}

void Scene::render(sf::RenderTarget &target)
{
    for (auto layer : layers.getHandle())
        for (auto obj : layer.second)
            obj->draw(target);
}
