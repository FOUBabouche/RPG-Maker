#include <elements/tileSelector.h>
#include <folderDialog.h>
#include <elements/animationPanel.h>
#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>

#include <cmath>
#include <string>

TileSelector::TileSelector(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
    textureContener.init("Project\\assets\\Textures");
    if(textureContener.getContentPaths().size())
        curentTexturePath = textureContener.getContentPaths()[0].filename();
    else
        curentTexturePath = "No texture";
}

void TileSelector::setBrush(Brush* brush){
    m_brushRef = brush;
}

void TileSelector::update(float dt)
{
    const int tileCountX = static_cast<int>(std::floor(static_cast<int>(m_brushRef->texture->getSize().x) / m_brushRef->uv.size.x));
    const int tileCountY = static_cast<int>(std::floor(static_cast<int>(m_brushRef->texture->getSize().y) / m_brushRef->uv.size.y));

    ImGui::Begin("Tile Selector");

    sf::Vector2f tileSize = {ImGui::GetContentRegionAvail().x / tileCountY-20, ImGui::GetContentRegionAvail().x/ tileCountY-20};

    ImGui::SeparatorText("Textures Paths");
    if(ImGui::BeginCombo("##Texture Path", curentTexturePath.string().c_str())){
        for (int i = 0; i < textureContener.getContentPaths().size(); i++)
        {
            bool isSelected = (curentTexturePath == textureContener.getContentPaths()[i]);
            if(ImGui::Selectable(textureContener.getContentPaths()[i].filename().string().c_str(), &isSelected)){
                curentTexturePath = textureContener.getContentPaths()[i].filename();
                m_brushRef->texture = new sf::Texture(std::filesystem::relative(textureContener.getContentPaths()[i]));
            }
        }
        if(bool click = false; ImGui::Selectable("Add Texture", &click)){
            textureContener.addFile(getPathByDialog());
        }
        ImGui::EndCombo();
    }

    ImGui::SeparatorText("TileSet");
    for(int x= 0; x< tileCountX; x++){
        for(int y= 0; y< tileCountY; y++){
            sf::Sprite sprite(*m_brushRef->texture);
            sprite.setTextureRect({{y * m_brushRef->uv.size.y, x * m_brushRef->uv.size.x}, m_brushRef->uv.size});
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
            if(ImGui::ImageButton(std::string("tile" + std::to_string(y)+ " "+std::to_string(x)).c_str(),sprite, tileSize)){
                m_brushRef->uv.position = {y * m_brushRef->uv.size.y, x * m_brushRef->uv.size.x};
            }
            if(ImGui::BeginDragDropSource()){
                GLuint glID = m_brushRef->texture->getNativeHandle();
                ImGui::SetDragDropPayload("Tile", &glID, sizeof(GLuint));
                ImGui::Image(sprite, {64,64});
                ImGui::Text("Drop it");
                ImGui::EndDragDropSource();

                if(auto animator = static_cast<Editor*>(m_editor)->getElement<AnimationPanel>("AnimationPanel")){
                    animator->setCurrentUVDragged({{y * m_brushRef->uv.size.y, x * m_brushRef->uv.size.x}, m_brushRef->uv.size});
                }
            }
            
            ImGui::SameLine();
            ImGui::PopStyleColor(3);
            ImGui::PopStyleVar();
        }
        ImGui::NewLine();
    }
    
    ImGui::End();
}