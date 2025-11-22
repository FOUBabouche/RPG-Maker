#include <elements/toolSelector.h>
#include <imgui.h>

ToolSelector::ToolSelector(std::string _name, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
}

void ToolSelector::update(float dt)
{
    if(ImGui::Begin("Tools")){
        for (auto& button : m_buttons){
            button.update(dt);
            ImGui::SameLine();
        }

        ImGui::End();
    }
}