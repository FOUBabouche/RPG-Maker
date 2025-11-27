#include <elements/consolePanel.h>

#include <imgui.h>
#include <imgui-SFML.h>

std::vector<std::pair<unsigned int, std::string>> ConsolePanel::m_lines = {};

ConsolePanel::ConsolePanel(std::string _name){
    name = _name;
}

bool ConsolePanel::lineExist(std::string arg){
    for(auto line : m_lines)
        if(line.second == arg)
            return true;
    return false;
}

size_t ConsolePanel::findLine(std::string line){
    for(size_t i = 0; i < m_lines.size(); i++)
        if(m_lines[i].second == line)
            return i;
    return -1;
}

void ConsolePanel::update(float dt) {
    if(m_lines.size() > 50)
        m_lines.erase(m_lines.begin());

    ImGui::Begin("Console");
    ImGui::BeginChild("##Console", ImGui::GetContentRegionAvail(), true);

    for (auto line : m_lines)
        ImGui::Text(("[DEBUG] ("+std::to_string(line.first)+") "+line.second).c_str());
    
    ImGui::EndChild();
    ImGui::End();
}