#ifndef __SHADER_EDITOR_H__
#define __SHADER_EDITOR_H__

#include <element.h>
#include <fileContener.h>

#include <SFML/Graphics/Shader.hpp>

class ShaderEditor : public Element{
    public:
        ShaderEditor() = default;
        ShaderEditor(std::string _name, Base_Editor* editor, const std::filesystem::path& path);
        ~ShaderEditor() = default;

        void update(float dt) override;
    private:
        std::filesystem::path currentShaderPath;
        FileContener shaderFolder;
        sf::Shader* shader = nullptr;
};

#endif