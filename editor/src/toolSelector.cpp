#include "toolSelector.h"
#include <imgui.h>

void ToolSelector::update()
{
    if(ImGui::Begin("Tools")){
        for (auto& button : m_buttons)
            button.update();

        ImGui::End();
    }
}