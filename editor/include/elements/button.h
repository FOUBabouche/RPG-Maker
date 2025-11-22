#ifndef __BUTOON_H__
#define __BUTTON_H__

#include <element.h>

#include <SFML/Graphics/Texture.hpp>

#include <functional>

class Button : public Element{
    public:
        Button();
        Button(std::string _name);
        Button(std::string _name, sf::Texture* iconRef);
        Button(const Button& button);
        ~Button() = default;

        void setIcon(sf::Texture* texRef, sf::IntRect uv, sf::Vector2f size);
        void setAction(std::function<void()> action);

        void update(float dt) override;

    public:
        Button& operator=(const Button& button);
    private:
        sf::Texture* m_textureRef = nullptr;
        sf::IntRect m_iconUV;

        std::function<void()> m_action;
};

#endif