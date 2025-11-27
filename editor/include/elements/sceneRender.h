#ifndef __SCENE_VIEW_H__
#define __SCENE_VIEW_H__

//Editor
#include <element.h>
#include <base_engine.h>
//Engine
#include <camera.h>
//External Lib
#include <SFML/Graphics/RenderTexture.hpp>
//STL
#include <memory>

class SceneRender : public Element{
    public:
        SceneRender();
        SceneRender(std::string _name, BaseEngine* engine, Base_Editor* editor);
        SceneRender(BaseEngine* engine, Base_Editor* editor);
        SceneRender(const SceneRender& render);
        ~SceneRender();

        sf::Vector2f getMousePositionInScene(Camera& camera);

        sf::RenderTexture* getHandle(void);

        void setEngine(BaseEngine* engine);

        void update(float dt) override;
    public:
        SceneRender& operator=(const SceneRender& render);
    private:
        sf::RenderTexture* m_renderer = nullptr;
        sf::Vector2f m_rendererPosition;
        BaseEngine* ref_engine = nullptr;
};

#endif