#include <sceneRender.h>
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_sfml_fix.h>
#include <iostream>

SceneRender::SceneRender()
{
    m_renderer = new sf::RenderTexture;
}

SceneRender::SceneRender(std::string _name, BaseEngine *engine)
{
    name = _name;
    ref_engine = engine;
    m_renderer = new sf::RenderTexture;
}


SceneRender::SceneRender(BaseEngine *engine)
{
    ref_engine = engine;
    m_renderer = new sf::RenderTexture;
}

SceneRender::SceneRender(const SceneRender &render)
{
    std::cout << render.m_renderer << std::endl;
    m_renderer = render.m_renderer;
    ref_engine = render.ref_engine;
}

SceneRender::~SceneRender()
{
    delete m_renderer;
}

sf::Vector2f SceneRender::getMousePositionInScene(Camera& camera)
{
    ImVec2 windowMousePos = ImGui::GetMousePos();

    sf::Vector2f renderLocalPos = { windowMousePos.x - m_rendererPosition.x, windowMousePos.y - m_rendererPosition.y };

	return (renderLocalPos + (camera.position - sf::Vector2f(camera.size.x / 2, camera.size.y / 2))) / camera.getZoom();
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
        ImGui::Image(m_renderer->getTexture(), {region.x, region.y},  {0, 1}, {1, 0});
        m_rendererPosition = {ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y};

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
