#ifndef __SCENE_INSPECTOR_PANEL__
#define __SCENE_INSPECTOR_PANEL__

#include <element.h>

class SceneInspectorPanel : public Element{
    public:
        SceneInspectorPanel() = default;
        SceneInspectorPanel(std::string _name, Base_Editor* editor);
        ~SceneInspectorPanel() = default;

        void update(float dt) override;
};

#endif