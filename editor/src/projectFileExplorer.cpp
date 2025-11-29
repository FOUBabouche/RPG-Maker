#include <elements/projectFileExplorer.h>
#include <elements/consolePanel.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/Texture.hpp>

#include <cmath>

ProjectFileExplorer::ProjectFileExplorer(std::string _name, Base_Editor *editor)
{
    name = _name;
    m_editor = editor;
    currentFolderPosition = "./Project";
    folderIcon = new sf::Texture("./ressources/editor/textures/folder.png");
    fileIcon = new sf::Texture("./ressources/editor/textures/file.png");
    
}

ProjectFileExplorer::~ProjectFileExplorer()
{
    delete fileIcon;
    delete folderIcon;
}

void ProjectFileExplorer::update(float dt)
{
    ImGui::Begin("File Explorer");
    if(currentFolderPosition.relative_path() != "./Project"){
        if(ImGui::Button("Return")){
            currentFolderPosition = currentFolderPosition.parent_path();
        }
    }
    ImGui::BeginChild("##FileExplorer", ImGui::GetContentRegionAvail(), true);

    int xCountMax = static_cast<int>(std::floor(ImGui::GetContentRegionAvail().x / 74));

    int i = 1;
    for(const auto& entry : std::filesystem::directory_iterator(currentFolderPosition)){
        ImGui::BeginGroup();
        if(entry.is_directory()){
            if(ImGui::ImageButton(entry.path().filename().string().c_str(),*folderIcon, {64, 64})){
                currentFolderPosition = entry.path().string();
            }
        }else{
            ImGui::ImageButton(entry.path().filename().string().c_str(),*fileIcon, {64, 64});
        }
        ImGui::Text(entry.path().filename().string().c_str());
        ImGui::EndGroup();

        if(xCountMax > 0){
            if(i % xCountMax != 0){
                ImGui::SameLine();
            }else{
                ImGui::NewLine();
            }
        }
        i++;
    }

    ImGui::EndChild();
    ImGui::End();
}
