#ifndef __SCENE_VIEW_H__
#define __SCENE_VIEW_H__

//Editor
#include <element.h>
#include <base_engine.h>
//Engine
#include <camera.h>
#include <shaderRenderer.h>
//External Lib
#include <SFML/Graphics/RenderTexture.hpp>
//STL
#include <memory>
#include <filesystem>

class SceneRender : public Element{
    public:
        SceneRender();
        SceneRender(std::string _name, BaseEngine* engine, Base_Editor* editor);
        SceneRender(BaseEngine* engine, Base_Editor* editor);
        SceneRender(const SceneRender& render);
        ~SceneRender();

        void setCurrentShader(const std::filesystem::path& shaderPath);
        void removeAllShader();

        sf::Vector2f getMousePositionInScene(Camera& camera);

        sf::RenderTexture* getHandle(void);

        void setEngine(BaseEngine* engine);

        void update(float dt) override;
    public:
        SceneRender& operator=(const SceneRender& render);
    private:
        sf::RenderTexture* m_renderer = nullptr;
        sf::RenderTexture* m_shader_renderer = nullptr;
        sf::Vector2f m_rendererPosition;
        BaseEngine* ref_engine = nullptr;
        ShaderRenderer shaderRenderer;
};

#endif