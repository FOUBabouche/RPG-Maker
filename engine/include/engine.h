#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <object.h>
#include <base_engine.h>
#include <vector>
#include <memory>

class Engine : virtual public BaseEngine{
    public:
        Engine() = default;
        ~Engine() = default;

        void addObject(Object* object);
        template<ObjectChild T>
        T* getObject(std::string name);
    private:
        std::vector<Object*> objects;
};

#endif