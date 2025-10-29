#include <engine.h>

void Engine::addObject(Object *object)
{
    for (auto& obj : objects)
        if(obj->name == object->name)
            return;
    
    objects.push_back(std::make_unique<Object>(object));
}

template<typename T>
T* Engine::getObject(std::string name){
    for (auto& obj : objects)
        if(obj->name == object->name)
            return static_cast<T*>(obj);
	return nullptr;
}