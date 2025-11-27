#ifndef __SCENE_H__
#define __SCENE_H__

#include <layers.h>

class Scene{
    public:
        Scene() = default;
        Scene(std::string name);
        ~Scene() = default;

        std::string getName(void) const;
        Layers& getLayers(void);

        std::string getCurrentLayerName(void) const;
        std::vector<Object*> getCurrentLayer(void);
        
        void setCurrentLayer(const std::string layerName);

        template<typename T>
        requires std::derived_from<T, Object>
        void addObject(std::string objName){
            if(layers.getHandle().size()>0)
                layers.addObjectToLayer<T>(currentLayerName, objName);
        }
        template<typename T>
        T* getObject(std::string name)
        {
            return layers.getObjectFromLayer<T>(currentLayerName, name);
        }

        template<typename T>
        T* getObject(std::string name, std::string layerName)
        {
            return layers.getObjectFromLayer<T>(layerName, name);
        }

        void addlayer(std::string layerName);

        void start();
        void update(float dt);
        void render(sf::RenderTarget& target);
    private:
        std::string m_name;
        Layers layers;
        std::string currentLayerName = "";
};

#endif