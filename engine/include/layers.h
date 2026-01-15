#ifndef __LAYERS_H__
#define __LAYERS_H__

#include <object.h>
#include <pluginObjectFunctions.h>

#include <string>
#include <vector>
#include <map>
#include <concepts>

class Layers{
    public:
        Layers() = default;
        Layers(PluginObjectManager* pom);
        ~Layers() = default;

        std::map<std::string, std::vector<Object *>>& getHandle(void);

        void addLayer(const std::string& name);

        void addWildObjectToLayer(const std::string layerName, Object* obj){
            if(!obj)return;
            int count = 0;
            for(auto _obj : layers[layerName]){
                if(_obj->name == obj->name) count++;
            }
            if(count>0) obj->name += ("("+std::to_string(count)+")");
            layers[layerName].push_back(obj);
        }

        template<typename T>
        void addObjectToLayer(const std::string layerName, std::string objName){
            int count = 0;
            for(auto _obj : layers[layerName]){
                if(_obj->name == objName) count++;
            }
            if(count>0) objName += ("("+std::to_string(count)+")");
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

        void clear();

    public:
        std::vector<Object*> operator[](const std::string& layerName);

    private:
        std::map<std::string, std::vector<Object*>> layers;
        PluginObjectManager* _pom;
};

#endif