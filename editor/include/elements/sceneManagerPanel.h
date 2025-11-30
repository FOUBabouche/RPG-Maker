#ifndef __SCENE_MANAGER_PANEL_H__
#define __SCENE_MANAGER_PANEL_H__

#include <element.h>

class SceneManagerPanel : public Element{
    public:
        SceneManagerPanel() = default;
        SceneManagerPanel(std::string _name, Base_Editor* editor);
        ~SceneManagerPanel() = default;

        void update(float dt) override;
    private:
        bool isNameMenuOpen = false;
};

#endif