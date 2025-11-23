#include <engine.h>

void Engine::addObject(Object *object)
{
    layers.addObjectToLayer(currentLayerName, object);
}

void Engine::setCurrentLayer(const std::string layerName)
{
    currentLayerName = layerName;
}

std::string Engine::getCurrentLayerName(void) const
{
    return currentLayerName;
}

Layers &Engine::getLayers(void)
{
    return layers;
}

void Engine::render(sf::RenderTarget &target)
{
    for(auto &layer : layers.getHandle()){
        for(auto& obj : layer.second)
            obj->draw(target);
    }
}