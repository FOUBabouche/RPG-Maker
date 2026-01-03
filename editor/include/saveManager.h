#ifndef __SAVE_MANAGER_H__
#define __SAVE_MANAGER_H__

#include <scene.h>

#include <filesystem>

class SaveManager{
    public:
        SaveManager() = default;
        ~SaveManager() = default;

        static void save(const std::string& saveName, Scene* scene);
        static void load(const std::filesystem::path& savePath);
};

#endif