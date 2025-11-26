#ifndef __LAYERS_H__
#define __LAYERS_H__

#include <object.h>

#include <string>
#include <vector>
#include <map>
#include <concepts>

class Layers{
    public:
        Layers() = default;
        ~Layers() = default;

        std::map<std::string, std::vector<Object *>>& getHandle(void);

        void addLayer(const std::string& name);
        template<typename T>
        requires std::derived_from<T, Object>
        void addObjectToLayer(const std::string layerName, std::string objName){
            layers[layerName].push_back(new T(objName));
        }

        template<typename T>
        T* getObjectFromLayer(std::string layerName, std::string objectName){
            for (auto &obj : layers[layerName])
                if (obj->name == objectName)
                    return static_cast<T*>(obj);
            return nullptr;
        }
      
        void removeLayer(std::string layerName);
        void removeObjectFromLayer(std::string layerName, std::string objectName);

    public:
        std::vector<Object*> operator[](const std::string& layerName);

    private:
        std::map<std::string, std::vector<Object*>> layers;
};

#endif