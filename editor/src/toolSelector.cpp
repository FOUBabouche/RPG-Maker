#include "toolSelector.h"
#include <imgui.h>

ToolSelector::ToolSelector(std::string _name)
{
    name = _name;
}

void ToolSelector::update()
{
    if(ImGui::Begin("Tools")){
        for (auto& button : m_buttons){
            button.update();
            ImGui::SameLine();
        }

        ImGui::End();
    }
}