#ifndef __BUTOON_H__
#define __BUTTON_H__

#include <element.h>

#include <SFML/Graphics/Texture.hpp>

#include <functional>

class Button : public Element{
    public:
        Button();
        ~Button() = default;

        void setIcon(sf::Texture* texRef, sf::IntRect uv, sf::Vector2f size);
        void setAction(std::function<void()> action);

        void update() override;
    private:
        unsigned int m_id;

        sf::Texture* m_textureRef;
        sf::IntRect m_iconUV;

        std::function<void()> m_action;
};

#endif