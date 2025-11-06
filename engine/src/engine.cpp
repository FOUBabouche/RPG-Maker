#include <engine.h>

void Engine::addObject(Object *object)
{
    for (auto obj : objects)
        if(obj->name == object->name)
            return;
    
    objects.push_back(object);
}

template<ObjectChild T>
T* Engine::getObject(std::string name){
    for (auto obj : this->objects)
        if(obj->name == name)
            return static_cast<T*>(&obj);
	return nullptr;
}