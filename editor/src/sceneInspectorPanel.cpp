#include <elements/sceneInspectorPanel.h>

#include <editor.h>

#include <camera.h>
#include <tilemap.h>
#include <camera.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <iostream>
#include <fstream>
#include <string>

SceneInspectorPanel::SceneInspectorPanel(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
}

void SceneInspectorPanel::update(float dt)
{
    ImGui::Begin("Scene Objects");
    ImGui::BeginChild("Objects", ImGui::GetContentRegionAvail(), true);
        if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
            ImGui::Text(engine->getCurrentScene()->getCurrentLayerName().c_str());
            
            static bool optionMenu = false;
            static bool nameMenu = false;
            static bool mouseOnOptionMenu = false;
            static std::string objName = "";

            if(ImGui::IsMouseClicked(ImGuiMouseButton_Right)){
                optionMenu = true;
            }
            if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !mouseOnOptionMenu){
                objName = "";
            }
            if(optionMenu){
                if (ImGui::BeginPopupContextWindow())
                {
                    if (ImGui::BeginMenu("Create"))
                    {
                        if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
                            if(ImGui::MenuItem("Camera")){
                                engine->getCurrentScene()->addObject<Camera>("Camera");
                                optionMenu = false;
                            }
                            if(ImGui::MenuItem("TileMap")){
                                if(auto tilemap = engine->getCurrentScene()->getObject<TileMap>("TileMap"); tilemap == nullptr){
                                    engine->getCurrentScene()->addObject<TileMap>("TileMap");
                                }
                                optionMenu = false;
                            }
                            if(ImGui::MenuItem("Auto Tile")){
                                optionMenu = false;
                            }
                            if(ImGui::BeginMenu("Objects")){
                                if(ImGui::MenuItem("Player")){
                                    
                                    optionMenu = false;
                                }
                                if(ImGui::MenuItem("NPC")){
                                    optionMenu = false;
                                }
                                if(ImGui::MenuItem("New Object")){
                                    nameMenu = true;
                                    optionMenu = false;
                                }
                                ImGui::EndMenu();
                            }
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::MenuItem("Delete"))
                    {
                        if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
                            engine->getCurrentScene()->getLayers().removeObjectFromLayer(engine->getCurrentScene()->getCurrentLayerName(),objName);
                        }
                        optionMenu = false;
                    }
                    mouseOnOptionMenu = ImGui::IsMouseHoveringRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
                    ImGui::EndPopup();
                }
            }

            for(auto& obj : engine->getCurrentScene()->getCurrentLayer()){
                ImGui::Button(obj->name.c_str(), {ImGui::GetContentRegionAvail().x, 20});
                bool mouseOnButton = ImGui::IsMouseHoveringRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
                if(mouseOnButton){
                    if(ImGui::IsMouseClicked(ImGuiMouseButton_Right)){
                        objName = obj->name;
                    }
                    continue;
                }else{
                    if(ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !mouseOnOptionMenu){
                        objName = "";
                    }
                }
            }
            
        }
    ImGui::EndChild();
    ImGui::End();
}