#include "shaderRenderer.h"
#include <camera.h>

#include <SFML/Graphics/Sprite.hpp>

#include <type_traits>

ShaderRenderer::ShaderRenderer(Object *object)
{
    holder = object;
}

void ShaderRenderer::addShader(const std::filesystem::path &shaderPath)
{
    sf::Shader shader(shaderPath, sf::Shader::Type::Fragment);
    shaders.push_back(shader);
}

void ShaderRenderer::display(bool state)
{
    isVisible = state;
}

void ShaderRenderer::increaseTotalTime(float value){
    totalTime += value;
}

void ShaderRenderer::draw(sf::RenderTarget &target)
{
    if(isVisible && holder){
        for(auto&& shader : shaders){
            sf::RenderTexture renderer;
            renderer.resize(static_cast<sf::Vector2u>(holder->size));
            sf::Sprite buffer(renderer.getTexture());
            if(std::same_as<decltype(*holder), Camera>){
                buffer.setPosition(holder->position-holder->size*0.5f);
            }else{
                buffer.setPosition(holder->position);
            }
            shader.setUniform("iTime", totalTime);
            shader.setUniform("iResolution", sf::Vector2f{(float)renderer.getSize().x,
                                                          (float)renderer.getSize().y});
            target.draw(buffer, &shader);
        }
    }
}
