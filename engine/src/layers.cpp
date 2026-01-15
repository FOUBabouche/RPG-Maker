#include <layers.h>

Layers::Layers(PluginObjectManager *pom)
{
    _pom = pom;
}

std::map<std::string, std::vector<Object *>> &Layers::getHandle(void)
{
    return layers;
}

void Layers::addLayer(const std::string& name)
{
    if(layers.count(name)>0) return;
    layers.insert({name, {}});
}

void Layers::removeLayer(std::string layerName)
{
    layers.erase(layers.find(layerName));
}

void Layers::removeObjectFromLayer(std::string layerName, std::string objectName)
{
    for (int i = 0; i < layers[layerName].size(); i++)
    {
        if(layers[layerName][i]->name == objectName){
            layers[layerName].erase(layers[layerName].begin()+i);
            return;
        }
    }   
}

void Layers::clear()
{
    for(auto layer : layers)
        for(auto obj: layer.second)
            if(!_pom) _pom->del(obj);
            else delete obj;
    layers.clear();
}

std::vector<Object *> Layers::operator[](const std::string &layerName)
{
    if(layers.count(layerName)==0) return {};
    return layers[layerName];
}