#ifndef __ELEMENT_H__
#define __ELEMENT_H__

#include <SFML/System/Vector2.hpp>

#include <concepts>
#include <string>

class Element{
    public:
        virtual ~Element() = default;

        virtual void update() = 0;
    public:
        std::string name;
    protected:
        sf::Vector2f m_size;
};

template<class T>
concept ElementChild = requires(T a){
    { std::hash<T>{}(a) }->std::derived_from<Element, T>;
};

#endif