#include <function_exporter.h>

extern "C" void deleteObject(Object *object)
{
    delete object;
}

__declspec(dllexport) void start(Object *object)
{
    object->start();
}

extern "C" __declspec(dllexport) void update(Object* object, float dt){
    object->update(dt);
}

extern "C" __declspec(dllexport) void render(Object* object, sf::RenderTarget& target){
    object->draw(target);
}

