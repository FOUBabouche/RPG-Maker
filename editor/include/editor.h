#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <base_editor.h>
#include <sceneRender.h>
#include <base_engine.h>
#include <element.h>

#include <vector>

class Editor : public Base_Editor{
    public:
        Editor();
        ~Editor();
        Editor(BaseEngine* engine);

        void addElement(Element* element);

        template<typename T>
        T* getElement(std::string name);

        void start() override;
        void update(float dt) override;
        void draw() override;

    private:
        std::vector<Element*> m_elements;
        BaseEngine* m_engineRef;
};

#endif
