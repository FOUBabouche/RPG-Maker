#include <sceneRender.h>
#include <imgui.h>
#include <imgui-SFML.h>

SceneRender::SceneRender(BaseEngine* engine)
{
    ref_engine = engine;
    m_renderer = std::make_unique<sf::RenderTexture>();
}

void SceneRender::update()
{
    if(ImGui::Begin("Scene")){
        ImVec2 region = ImGui::GetContentRegionAvail();
        ImGui::Image(*m_renderer, {region.x, region.y});

        ImGui::End();
    }
}

void SceneRender::draw()
{
    m_renderer->clear();
    ref_engine->render(*m_renderer);
    m_renderer->display();
}
