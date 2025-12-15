#ifndef __SHADER_RENDERER_H__
#define __SHADER_RENDERER_H__

#include <object.h>

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <filesystem>
#include <vector>

class ShaderRenderer{
    public:
        ShaderRenderer() = default;
        ShaderRenderer(Object* object);
        
        void addShader(const std::filesystem::path& shaderPath);
        void display(bool state);

        void increaseTotalTime(float value);

        void draw(sf::RenderTarget& target);

    private:
        float totalTime = 0;
        Object* holder;
        std::vector<sf::Shader> shaders;
        bool isVisible = false;
};

#endif