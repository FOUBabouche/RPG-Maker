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
        Script script(scriptName, static_cast<Editor*>(m_editor)->getProject());
        script.create()
                .registerClass(scriptName)
                .addInclude("object.h")
                .addMethodeToClass(scriptName,"start()")
                .addMethodeToClass(scriptName,"update(float dt)")
                .addMethodeToClass(scriptName,"draw(sf::RenderTarget& target)")
                .build();
        script.prepareToExport();
    }

    ImGui::End();
}