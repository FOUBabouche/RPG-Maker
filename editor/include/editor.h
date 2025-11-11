#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <base_editor.h>
#include <sceneRender.h>
#include <engine.h>
#include <element.h>

#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <vector>

class Editor : public Base_Editor{
    public:
        Editor();
        Editor(Engine* engine);
        ~Editor();

        void addElement(Element* element);

        template<typename T>
        T* getElement(std::string name);

        void start() override;
        void update(float dt) override;

    private:
        std::vector<Element*> m_elements;
        Engine* m_engineRef;

        std::unordered_map<std::string, sf::Texture*> buttonsTextures;
};

#endif
