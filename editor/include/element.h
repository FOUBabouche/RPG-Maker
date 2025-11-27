#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <base_editor.h>

#include <SFML/System/Vector2.hpp>

#include <concepts>
#include <string>

class Element{
    public:
        virtual ~Element() = default;

        virtual void update(float dt) = 0;
    public:
        std::string name;
    protected:
        sf::Vector2f m_size;
        Base_Editor* m_editor;
};

#endif