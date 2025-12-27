#include <elements/shaderEditor.h>
#include <elements/sceneRender.h>

#include <editor.h>

#include <imgui.h>
#include <imgui-SFML.h>

ShaderEditor::ShaderEditor(std::string _name, Base_Editor* editor, const std::filesystem::path& path){
    name = _name;
    m_editor = editor;
    shaderFolder = FileContener(path);
    if(shaderFolder.getContentPaths().size()> 0)
        currentShaderPath = shaderFolder.getContentPaths()[0];
}

void ShaderEditor::update(float dt)
{
    ImGui::Begin("Shader Editor");
        
    // Drop scroll avec la liste des fichier de shader
    if(ImGui::BeginCombo("Shader List", currentShaderPath.filename().string().c_str())){
        for(auto shaderPath : shaderFolder.getContentPaths()){
            if(ImGui::Selectable(shaderPath.filename().string().c_str(), false)){
                currentShaderPath = shaderPath;
                if(auto renderer = static_cast<Editor*>(m_editor)->getElement<SceneRender>("Renderer")){
                    renderer->setCurrentShader(currentShaderPath);
                }
            }
        }
        if(ImGui::Selectable("No Shader", false)){
            currentShaderPath = "No Shader";
            if(auto renderer = static_cast<Editor*>(m_editor)->getElement<SceneRender>("Renderer")){
                renderer->removeAllShader();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::End();
}
