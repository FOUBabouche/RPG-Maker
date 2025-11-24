#ifndef __SAVE_MANAGER_H__
#define __SAVE_MANAGER_H__

#include <nlohmann-json/json.hpp>

class SaveManager{
    public:
        SaveManager() = default;
        ~SaveManager() = default;

        void save();
        void load();
};

#endif