#include <button.h>
#include <imgui-SFML.h>
#include <imgui.h> 

Button::Button()
{
    m_textureRef = nullptr;
    m_iconUV = {{0, 0}, {16, 16}};
    m_size = {50, 50};
    m_id++;
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

void Button::update()
{
    if(ImGui::ImageButton(std::to_string(m_id).c_str(), *m_textureRef, m_size)) m_action();
}
