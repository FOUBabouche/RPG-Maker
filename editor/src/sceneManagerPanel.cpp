#include <elements/sceneManagerPanel.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>

SceneManagerPanel::SceneManagerPanel(std::string _name, Base_Editor* editor){
    name = _name;
    m_editor = editor;
}

void SceneManagerPanel::update(float dt){
    ImGui::Begin("Scene Manager");

    if(ImGui::BeginCombo("Scene List", static_cast<Editor*>(m_editor)->getEngine()->getCurrentScene()->getName().c_str())){
        for(auto scene : static_cast<Editor*>(m_editor)->getEngine()->getScenes()){
            bool selected = static_cast<Editor*>(m_editor)->getEngine()->getCurrentScene()->getName() == scene->getName();
            if(ImGui::Selectable(scene->getName().c_str(), &selected)){
                static_cast<Editor*>(m_editor)->getEngine()->setCurrentScene(scene->getName());
            }
        }
        if(ImGui::Selectable("Add Scene", false)){
            isNameMenuOpen = true;
        }
        ImGui::EndCombo();
    }

    if(isNameMenuOpen){
        ImGui::OpenPopup("Scene name", ImGuiPopupFlags_AnyPopupLevel);
        if(ImGui::BeginPopupModal("Scene name")){
            char buffer[256] = "";
            if(ImGui::InputText("Scene name", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue)){
                static_cast<Editor*>(m_editor)->getEngine()->addScene(std::string(buffer));
                isNameMenuOpen = false;
            }
            ImGui::EndPopup();
        }
    }

    ImGui::End();
}