#include <brushPanel.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/Sprite.hpp>

#include <string>

// Compile-time template
    template <auto V>
    std::string EnumToString() {
#if defined(__clang__) || defined(__GNUC__)
        std::string_view s = __PRETTY_FUNCTION__;
        auto pos = s.find("V = ") + 4;
        auto end = s.find(']', pos);
        return std::string(s.substr(pos, end - pos));
#elif defined(_MSC_VER)
        std::string_view s = __FUNCSIG__;
        auto pos = s.rfind("::") + 2;
        auto end = s.find('>', pos);
        return std::string(s.substr(pos, end - pos));
#else
        return "???";
#endif
    }

// IIFE lambda template
template<typename E, std::size_t Max = 256>
std::string EnumToString(E value) {
    std::string result;
    [&] <std::size_t... Is>(std::index_sequence<Is...>) {
        ((value == static_cast<E>(Is) ? (result = EnumToString<static_cast<E>(Is)>(), true) : false) || ...);
    }(std::make_index_sequence<Max>{});
    return result.empty() ? "Unknown" : result;
}

BrushPanel::BrushPanel(std::string _name)
{
    name = _name;
    brush.color = sf::Color::White;
    brush.uv = {{0, 0}, {64, 64}};
}

BrushPanel::~BrushPanel()
{

}

Brush &BrushPanel::getBrush(void)
{
    return brush;
}

void BrushPanel::update()
{
    if(ImGui::Begin("Brush")){
        ImGui::SeparatorText("Properties");
        if(ImGui::BeginCombo("Brush Type", EnumToString(tileType).c_str())){
            for (int i = 0; i < static_cast<int>(TILE_TYPE::TRANSPARENT_TILE)+1; i++)
            {
                bool isSelected = (tileType == static_cast<TILE_TYPE>(i));
                if(ImGui::Selectable(EnumToString(static_cast<TILE_TYPE>(i)).c_str(), &isSelected)){
                    tileType = static_cast<TILE_TYPE>(i);
                }
            }
            ImGui::EndCombo();
        }

        int uvPos[2] = {brush.uv.position.x, brush.uv.position.y};
        if(ImGui::InputInt2(std::string("X-Y").c_str(), uvPos)){
            brush.uv.position = {uvPos[0], uvPos[1]};
        }
        int uvSize[2] = {brush.uv.size.x, brush.uv.size.y};
        if(ImGui::InputInt2(std::string("Width-Height").c_str(), uvSize)){
            brush.uv.size = {uvSize[0], uvSize[1]};
        }

        ImGui::SeparatorText("Preview");
        sf::Sprite sprite(*brush.texture);
        sprite.setTextureRect(brush.uv);
        ImGui::Image(sprite, {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x}, brush.color);

        ImGui::End();
    }
}