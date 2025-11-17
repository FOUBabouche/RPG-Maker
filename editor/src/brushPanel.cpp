#include <brushPanel.h>
#include <imgui.h>
#include <imgui-SFML.h>

#include <string>

#define CONVERTER(x) TILE_TYPE y = x return y

template <auto V>
std::string EnumToString(V enumVar) {
    std::string_view s = __PRETTY_FUNCTION__;
    auto pos = s.find("V = ") + 4;
    auto end = s.find(']', pos);
    return std::string(s.substr(pos, end - pos));
}

BrushPanel::BrushPanel(std::string _name)
{
    name = _name;
}

void BrushPanel::update()
{

    std::string preview = EnumToString<tileType>();
    if(ImGui::Begin("Brush")){
        ImGui::SeparatorText("Brush Type");
        
        if(ImGui::BeginCombo("bruszhtype", preview.c_str())){
            bool isSelected = (tileType == TILE_TYPE::NORMAL_TILE);
            if(ImGui::Selectable("Normal Tile"), &isSelected){
                tileType = TILE_TYPE::NORMAL_TILE;
            }
             isSelected = (tileType == TILE_TYPE::ANIMATED_TILE);
            if(ImGui::Selectable("Animated Tile", &isSelected)){
                tileType = TILE_TYPE::ANIMATED_TILE;
            }
             isSelected = (tileType == TILE_TYPE::COLLISION_TILE);
            if(ImGui::Selectable("Collision Tile", &isSelected)){
                tileType = TILE_TYPE::COLLISION_TILE;
            }
             isSelected = (tileType == TILE_TYPE::TRANSPARENT_TILE);
            if(ImGui::Selectable("Transparent Tile", &isSelected)){
                tileType = TILE_TYPE::TRANSPARENT_TILE;
            }
            ImGui::EndCombo();
        }
        ImGui::SeparatorText("Properties");

        ImGui::SeparatorText("Preview");
        

        ImGui::End();
    }
}