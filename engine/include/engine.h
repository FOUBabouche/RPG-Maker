#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <object.h>
#include <layers.h>
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
            return layers.getObjectFromLayer<T>(currentLayerName, name);
        }

        void setCurrentLayer(const std::string layerName);
        std::string getCurrentLayerName(void) const;

        Layers& getLayers(void);

        void render(sf::RenderTarget& target) override;
    protected:
        std::vector<Object*> m_objects;
        Layers layers;
        std::string currentLayerName = "";
};

#endif