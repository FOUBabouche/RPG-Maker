#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <base_editor.h>
#include <elements/sceneRender.h>
#include <engine.h>
#include <element.h>

#include <SFML/Graphics/Texture.hpp>

#include <unordered_map>
#include <vector>

enum Tools{
    Select,
    Move,
    Paint,
    Erase
};

class Editor : public Base_Editor{
    public:
        Editor() = default;
        Editor(Engine* engine);
        ~Editor();

        void addElement(Element* element);

        template<typename T>
        T* getElement(std::string name)
        {
            for(auto obj : m_elements) 
                if (obj->name == name) return static_cast<T*>(obj);
            return nullptr;
        }

        Engine* getEngine(void) const;

        void start() override;
        void update(float dt) override;

    private:
        void registerTextures();
        void registerElements();
        void registerToolButtons();

    private:
        std::vector<Element*> m_elements;
        Engine* m_engineRef;

        Tools m_tool = Tools::Select;

        std::unordered_map<std::string, sf::Texture*> buttonsTextures;
        sf::Texture* placeHolder;
};

#endif
