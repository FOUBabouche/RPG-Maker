#include <tileSelector.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/Sprite.hpp>

#include <cmath>
#include <string>

TileSelector::TileSelector(std::string _name)
{
    name = _name;
}

void TileSelector::setBrush(Brush* brush){
    m_brushRef = brush;
}

void TileSelector::update()
{
    const int tileCountX = static_cast<int>(std::floor(static_cast<int>(m_brushRef->texture->getSize().x) / m_brushRef->uv.size.x));
    const int tileCountY = static_cast<int>(std::floor(static_cast<int>(m_brushRef->texture->getSize().y) / m_brushRef->uv.size.y));
    if(ImGui::Begin("Tile Selector")){
        sf::Vector2f tileSize = {ImGui::GetContentRegionAvail().x / tileCountY-20, ImGui::GetContentRegionAvail().x/ tileCountY-20};
        ImGui::SeparatorText("TileSet");
        for(int x= 0; x< tileCountX; x++){
            for(int y= 0; y< tileCountY; y++){
                sf::Sprite sprite(*m_brushRef->texture);
                sprite.setTextureRect({{y * m_brushRef->uv.size.y, x * m_brushRef->uv.size.x}, m_brushRef->uv.size});
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
                if(ImGui::ImageButton(std::string("tile" + std::to_string(y)+ " "+std::to_string(x)).c_str(),sprite, tileSize)){
                    m_brushRef->uv.position = {y * m_brushRef->uv.size.y, x * m_brushRef->uv.size.x};
                }
                ImGui::PopStyleColor(3);
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }

        ImGui::End();
    }
}