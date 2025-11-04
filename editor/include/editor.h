#ifndef EDITOR_H
#define EDITOR_H

#include <base_editor.h>

class Editor : public Base_Editor{
    public:
        void start() override;
        void update(float dt) override;
        void draw(sf::RenderTarget& target) override;
};

#endif