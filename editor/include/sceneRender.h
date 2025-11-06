#ifndef __SCENE_VIEW_H__
#define __SCENE_VIEW_H__

#include <element.h>
#include <base_engine.h>

#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>

class SceneRender : public Element{
    public:
        SceneRender();
        SceneRender(const SceneRender& render);
        SceneRender(BaseEngine* engine);
        ~SceneRender();

        void setEngine(BaseEngine* engine);

        void update() override;
    public:
        SceneRender& operator=(const SceneRender& render);
    private:
        sf::RenderTexture* m_renderer = nullptr;
        BaseEngine* ref_engine = nullptr;
};

#endif