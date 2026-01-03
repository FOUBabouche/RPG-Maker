#include <saveManager.h>
#include <fstream>

#include <nlohmann/json.hpp>

void SaveManager::save(const std::string &saveName, Scene *scene)
{
    using nlohmann::json;
    json js;
    // js["Contents"].push_back({"Layers", {}});
    for(auto [layerName, objects] : scene->getLayers().getHandle()){
        for(auto object : objects){
            // js["Contents"]["Layers"].push_back({layerName, {}});
            js["Contents"]["Layers"][layerName][object->name]["position"] = {
                {"x", object->position.x}, {"y", object->position.y}
            };

            js["Contents"]["Layers"][layerName][object->name]["size"] = {
                {"x", object->size.x}, {"y", object->size.y}
            };
        }
    }
    std::ofstream saveFile("./Project/assets/Scenes/"+saveName+".json");
    saveFile << std::setw(4) << js;
    saveFile.close();
}

void SaveManager::load(const std::filesystem::path &savePath)
{
}
