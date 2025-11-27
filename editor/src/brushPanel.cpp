#include <elements/brushPanel.h>
#include <tilemap.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/Sprite.hpp>

#include <string>
#include <iostream>

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

BrushPanel::BrushPanel(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
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

Tile &BrushPanel::currentAnimatedTile(void)
{
    return currentAnimatedTileSelected;
}

    
TILE_TYPE BrushPanel::getTileType(void) const
{
    return tileType;
}

void BrushPanel::addAnimatedTile(const Tile& tile)
{
    animatedTiles.push_back(tile);
}

void BrushPanel::update(float dt)
{
    ImGui::Begin("Brush");
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

    if(tileType == TILE_TYPE::NORMAL_TILE){
        ImGui::SeparatorText("Preview");
        sf::Sprite sprite(*brush.texture);
        sprite.setTextureRect(brush.uv);
        ImGui::Image(sprite, {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x}, brush.color);
    }
    if(tileType == TILE_TYPE::ANIMATED_TILE){
        ImGui::SeparatorText("Animated Tiles");
        for(auto animatedTile : animatedTiles){
            animatedTile.update(dt);
            sf::Sprite sprite(*animatedTile.getTextureRef());
            sprite.setTextureRect(animatedTile.getUV());
            if(ImGui::ImageButton(std::to_string(reinterpret_cast<unsigned long long>(&animatedTile)).c_str(),sprite, {32, 32})){
                currentAnimatedTileSelected = animatedTile;
            }
        }
    }

    ImGui::SeparatorText("Layers");
    if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
        if(auto scene = engine->getCurrentScene()){
            if(ImGui::BeginCombo("##Layers", scene->getCurrentLayerName().c_str())){
                for (auto layer : scene->getLayers().getHandle())
                {
                    bool selected = scene->getCurrentLayerName() == layer.first;
                    if(ImGui::Selectable(layer.first.c_str(), &selected)){
                        scene->setCurrentLayer(layer.first);
                    }
                }
                if(bool selected = false; ImGui::Selectable("Add Layer", &selected)){
                    scene->getLayers().addLayer("Layer " + std::to_string(scene->getLayers().getHandle().size() + 1));
                    scene->setCurrentLayer("Layer " + std::to_string(scene->getLayers().getHandle().size()));
                    scene->addObject<TileMap>("TileMap");
                }
                ImGui::EndCombo();
            }
        }
    }
    bool checked = true;
    if(ImGui::Checkbox("Have Collision", &checked)){
        // TODO
    }
        
    ImGui::End();
}