#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <base_editor.h>
#include <element.h>

#include <vector>

class Editor : public Base_Editor{
    public:
        void start() override;
        void update(float dt) override;
        void draw() override;

    private:
        std::vector<Element> elements;
};

#endif