#include <engine.h>

void Engine::addObject(Object *object)
{
    for (auto obj : m_objects)
        if(obj->name == object->name)
            return;
    
    m_objects.push_back(object);
}

void Engine::render(sf::RenderTarget &target)
{
    for(auto& obj : m_objects)
        obj->draw(target);
}

template<ObjectChild T>
T* Engine::getObject(std::string name){
    for (auto obj : m_objects)
        if(obj->name == name)
            return static_cast<T*>(&obj);
	return nullptr;
}