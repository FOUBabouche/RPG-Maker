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
        template<typename T>
        T* getObject(std::string name)
        {
            for (auto obj : m_objects)
                if (obj->name == name)
                    return static_cast<T*>(obj);
            return nullptr;
        }

        void render(sf::RenderTarget& target) override;
    protected:
        std::vector<Object*> m_objects;
};

#endif