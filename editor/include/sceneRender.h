#ifndef __SCENE_VIEW_H__
#define __SCENE_VIEW_H__

#include <element.h>
#include <base_engine.h>

#include <SFML/Graphics/RenderTexture.hpp>

#include <memory>

class SceneRender : public Element{
    public:
        SceneRender(BaseEngine* engine);
        ~SceneRender() = default;

        void update() override;
        void draw() override;
    private:
        std::unique_ptr<sf::RenderTexture> m_renderer;
        BaseEngine* ref_engine;
};

#endif