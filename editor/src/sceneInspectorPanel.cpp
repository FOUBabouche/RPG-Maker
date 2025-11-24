#include <elements/sceneInspectorPanel.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>

SceneInspectorPanel::SceneInspectorPanel(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
}

void SceneInspectorPanel::update(float dt)
{
    if(ImGui::Begin("Scene Objects")){
        if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
            ImGui::Text(engine->getCurrentScene()->getCurrentLayerName().c_str());
            if(ImGui::BeginChild("Objects", ImGui::GetContentRegionAvail(), true)){
                static std::string objName = "";
                for(auto& obj : engine->getCurrentScene()->getCurrentLayer()){
                    ImGui::Button(obj->name.c_str(), {ImGui::GetContentRegionAvail().x, 20});
                    if(ImGui::IsItemHovered() && ImGui::IsMouseClicked(1)){
                        objName = obj->name;
                    }
                }
                if(objName != ""){
                    if (ImGui::BeginPopupContextWindow())
                    {
                        if (ImGui::MenuItem("Delete"))
                        {
                            if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
                                engine->getCurrentScene()->getLayers().removeObjectFromLayer(engine->getCurrentScene()->getCurrentLayerName(),objName);
                            }
                        }
                        ImGui::EndPopup();
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();
    }
}
