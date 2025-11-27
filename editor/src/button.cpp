#include <elements/button.h>
#include <imgui-SFML.h>
#include <imgui.h> 

Button::Button()
{
    name = "Button";
    m_textureRef = 0;
    m_iconUV = {{0, 0}, {16, 16}};
    m_size = {50, 50};
}

Button::Button(std::string _name)
{
    name = _name;
    m_textureRef = 0;
    m_iconUV = {{0, 0}, {16, 16}};
    m_size = {50, 50};
}

Button::Button(std::string _name, sf::Texture *iconRef)
{
    name = _name;
    m_textureRef = iconRef;
    m_iconUV = {{0, 0}, {16, 16}};
    m_size = {50, 50};
}

Button::Button(const Button &button)
{
    m_textureRef = button.m_textureRef;
    m_iconUV = button.m_iconUV;
    m_size = button.m_size;
    name = button.name;
}

void Button::setIcon(sf::Texture *texRef, sf::IntRect uv, sf::Vector2f size)
{
    m_textureRef = texRef;
    m_iconUV = uv;
    m_size = size;
}

void Button::setAction(std::function<void()> action)
{
    m_action = action;
}

void Button::update(float dt)
{
    if(m_textureRef){
        if(ImGui::ImageButton(name.c_str(), *m_textureRef, {ImGui::GetContentRegionAvail().y-3, ImGui::GetContentRegionAvail().y-3})){
            if(m_action != nullptr)m_action();
        }
    }else{
        if(ImGui::Button(name.c_str(), {m_size.x, m_size.y})){
            if(m_action != nullptr)m_action();
        }
    }
    
}

Button &Button::operator=(const Button &button)
{
    m_textureRef = button.m_textureRef;
    m_iconUV = button.m_iconUV;
    m_size = button.m_size;
    name = button.name;
    return *this;
}
