#include <elements/scriptCreator.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>

#include <script.h>

ScriptCreator::ScriptCreator(std::string _name, Base_Editor *editor)
{
    name = _name;
    m_editor = editor;
}

void ScriptCreator::update(float dt)
{
    ImGui::Begin("Scripting");

    ImGui::InputText("Name", scriptName, 256);
    
    if(ImGui::Button("Create")){
        Script script(std::string(scriptName), nullptr);
    }

    ImGui::End();
}