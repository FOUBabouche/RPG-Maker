#include <sceneRender.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

SceneRender::SceneRender()
{
    m_renderer = new sf::RenderTexture;
}

SceneRender::SceneRender(const SceneRender &render)
{
    std::cout << render.m_renderer << std::endl;
    m_renderer = render.m_renderer;
    ref_engine = render.ref_engine;
}

SceneRender::SceneRender(BaseEngine *engine)
{
    ref_engine = engine;
    m_renderer = new sf::RenderTexture;
}

SceneRender::~SceneRender()
{
    delete m_renderer;
}

void SceneRender::setEngine(BaseEngine *engine)
{
    ref_engine = engine;
}

void SceneRender::update()
{
    m_renderer->clear(sf::Color::Black);
    ref_engine->render(*m_renderer);
    m_renderer->display();

    if(ImGui::Begin("Scene")){
        ImVec2 region = ImGui::GetContentRegionAvail();
        m_renderer->resize({static_cast<unsigned int>(region.x), static_cast<unsigned int>(region.y)});
        ImGui::Image(m_renderer->getTexture(), {region.x, region.y});

        ImGui::End();
    }
}



SceneRender &SceneRender::operator=(const SceneRender &render)
{
    std::cout << render.m_renderer << std::endl;
    m_renderer = render.m_renderer;
    ref_engine = render.ref_engine;
    return *this;
}
