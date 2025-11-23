#include <elements/animationPanel.h>
#include <elements/brushPanel.h>
#include <tile.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>

AnimationPanel::AnimationPanel(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
}

void AnimationPanel::setCurrentUVDragged(const sf::IntRect &uv)
{
    m_currentUv = uv;
}

void AnimationPanel::update(float dt)
{
    if(ImGui::Begin("Animations")){
        if(ImGui::Button("Create")){
            if(m_uvs.size() > 0){
                if(auto brushPanel = static_cast<Editor*>(m_editor)->getElement<BrushPanel>("BrushPanel")){
                    brushPanel->addAnimatedTile(Tile({0, 0}, {16, 16}, m_uvs, brushPanel->getBrush().texture));
                }
            }
        }
        ImGui::SameLine();
        if(ImGui::Button(isPlaying ? "Stop" : "Play")){
            isPlaying =! isPlaying;
        }
        if(ImGui::BeginChild("Drop Zone", {ImGui::GetContentRegionAvail().x * 0.8f, ImGui::GetContentRegionAvail().y}, true))
        {
            ImGui::InvisibleButton("DropZoneButton", ImGui::GetContentRegionAvail());
            ImGui::SetItemAllowOverlap();
            if(ImGui::BeginDragDropTarget()){
                if(const auto data = ImGui::AcceptDragDropPayload("Tile")){
                    std::cout << "Droped" << std::endl;
                    m_uvs.push_back(m_currentUv);
                }
                ImGui::EndDragDropTarget();
            }
            ImGui::SetCursorPos(ImGui::GetWindowContentRegionMin());
            static unsigned int id = 0;
            for (unsigned int i = 0; i < m_uvs.size(); i++)
            {
                sf::Sprite sprite(*static_cast<Editor*>(m_editor)->getElement<BrushPanel>("BrushPanel")->getBrush().texture);
                sprite.setTextureRect(m_uvs[i]);
                ImGui::Image(sprite, {128, 128});
                if(ImGui::IsItemHovered() && ImGui::IsMouseClicked(1)){
                    id = i;
                }
                ImGui::SameLine();
            }
            if (ImGui::BeginPopupContextWindow())
            {
                isPlaying = false;
                if (ImGui::MenuItem("Delete"))
                {
                    m_uvs.erase(m_uvs.begin()+id);
                }
                ImGui::EndPopup();
            }
            ImGui::EndChild();            
        }
        ImGui::SameLine();
        if(ImGui::BeginChild("Preview Zone",ImGui::GetContentRegionAvail(), true))
        {
            sf::Sprite sprite(*static_cast<Editor*>(m_editor)->getElement<BrushPanel>("BrushPanel")->getBrush().texture);
            if(isPlaying){
                if(totalTime >= 1 * animationSpeed){
                    currentUVIndex++;
                    if(currentUVIndex == m_uvs.size()){
                        currentUVIndex = 0;
                    }
                    totalTime = 0;
                }else{ 
                    totalTime += dt;
                }
            }
            if(m_uvs.size() > 0){
                sprite.setTextureRect(m_uvs[currentUVIndex]);
                ImGui::Image(sprite, {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x});
            }
            ImGui::EndChild();
        }
        
        ImGui::End();
    }
}
