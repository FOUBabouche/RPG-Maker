#ifndef __SAVE_MANAGER_H__
#define __SAVE_MANAGER_H__

class SaveManager{
    public:
        SaveManager() = default;
        ~SaveManager() = default;

        void save();
        void load();
};

#endif