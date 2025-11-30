#include <engine.h>

std::vector<Scene *> Engine::getScenes(void) const
{
    return scenes;
}

Scene *Engine::getScene(std::string sceneName) const
{
    for(auto scene : scenes){
        if(scene->getName() == sceneName){
            return scene;
        }
    }
    return nullptr;
}

Scene *Engine::getCurrentScene(void) const
{
    return scenes[currentSceneIndex];
}

void Engine::setCurrentScene(std::string sceneName)
{
    if(!getScene(sceneName)) return;
    for(int i = 0; i < scenes.size(); i++){
        if(scenes[i]->getName() == sceneName){
            currentSceneIndex = i;
        }
    }
}

void Engine::setCurrentScene(size_t sceneIndex)
{
    if(scenes.size()<=sceneIndex)return;
    currentSceneIndex = sceneIndex;
}

void Engine::addScene(std::string sceneName)
{
    if(getScene(sceneName)) return;
    scenes.push_back(new Scene(sceneName));
}

void Engine::clear()
{
    for(auto scene : scenes)
        delete scene;
    scenes.clear();
}

void Engine::render(sf::RenderTarget &target)
{
    if(scenes.size()>0)
        scenes[currentSceneIndex]->render(target);
}