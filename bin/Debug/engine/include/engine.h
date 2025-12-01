#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <object.h>
#include <scene.h>
#include <base_engine.h>
#include <vector>
#include <memory>

class Engine : virtual public BaseEngine{
    public:
        Engine() = default;
        ~Engine() = default;

        std::vector<Scene*> getScenes(void) const;
        Scene* getScene(std::string sceneName) const;
        Scene* getCurrentScene(void) const;

        void setCurrentScene(std::string sceneName);
        void setCurrentScene(size_t sceneIndex);

        void addScene(std::string scenename);

        void clear();

        void render(sf::RenderTarget& target) override;
    protected:
        std::vector<Scene*> scenes;
        size_t currentSceneIndex = 0;
};

#endif