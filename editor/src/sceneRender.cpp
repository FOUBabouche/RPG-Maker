#include <elements/sceneRender.h>

#include <editor.h>

#include <camera.h>
#include <tilemap.h>

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_sfml_fix.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <iostream>

SceneRender::SceneRender()
{
    m_renderer = new sf::RenderTexture;
    m_shader_renderer = new sf::RenderTexture;
}

SceneRender::SceneRender(std::string _name, BaseEngine *engine, Base_Editor* editor)
{
    name = _name;
    m_editor = editor;
    ref_engine = engine;
    m_renderer = new sf::RenderTexture;
    m_shader_renderer = new sf::RenderTexture;
}


SceneRender::SceneRender(BaseEngine *engine, Base_Editor* editor)
{
    ref_engine = engine;
    m_editor = editor;
    m_renderer = new sf::RenderTexture;
    m_shader_renderer = new sf::RenderTexture;
}

SceneRender::SceneRender(const SceneRender &render)
{
    m_renderer = render.m_renderer;
    ref_engine = render.ref_engine;
    m_shader_renderer = render.m_shader_renderer;
}

SceneRender::~SceneRender()
{
    delete m_shader_renderer;
    delete m_renderer;
}

void SceneRender::setCurrentShader(sf::Shader* shader){
    currentUsedShader = shader;
}

sf::RenderTexture* SceneRender::getHandle(void){
    return m_renderer;
}

sf::Vector2f SceneRender::getMousePositionInScene(Camera& camera)
{
    ImVec2 mouseImGui = ImGui::GetMousePos();
    sf::Vector2f local = { mouseImGui.x - m_rendererPosition.x, mouseImGui.y - m_rendererPosition.y };

    sf::Vector2f rendererPx = static_cast<sf::Vector2f>(m_renderer->getSize());

    // calculer la taille du view en unités monde (après zoom)
    sf::Vector2f viewSizeWorld = camera.size * camera.getZoom(); // opérateur * scalaire à implémenter si besoin

    sf::Vector2f normalized = { local.x / rendererPx.x, local.y / rendererPx.y };

    sf::Vector2f camTopLeft = camera.position - 0.5f * viewSizeWorld;

    sf::Vector2f mouseWorld = camTopLeft + sf::Vector2f(normalized.x * viewSizeWorld.x, normalized.y * viewSizeWorld.y);

    return mouseWorld;
}

void SceneRender::setEngine(BaseEngine *engine)
{
    ref_engine = engine;
}

void SceneRender::update(float dt)
{
    m_renderer->clear(sf::Color::Black);
    if(m_shader_renderer && currentUsedShader){
        sf::Sprite shaderBuffer(m_shader_renderer->getTexture());
        m_shader_renderer->resize(m_renderer->getSize());
        currentUsedShader->setUniform("iTime", dt);
        currentUsedShader->setUniform("iResolution", sf::Vector2i{(int)m_shader_renderer->getSize().x,
                                                                  (int)m_shader_renderer->getSize().y});
        m_renderer->draw(shaderBuffer, currentUsedShader);
    }
    ref_engine->render(*m_renderer);
    if(auto engine = static_cast<Editor*>(m_editor)->getEngine()){
        if(auto tilemap = engine->getCurrentScene()->getObject<TileMap>("TileMap")){
            Camera& camera = static_cast<Editor*>(m_editor)->getCamera();
            tilemap->drawGrid(*m_renderer, camera.position, m_rendererPosition, camera.getZoom());
        }
    }
    m_renderer->display();

    ImGui::Begin("Scene");
    ImVec2 region = ImGui::GetContentRegionAvail();
    m_renderer->resize({static_cast<unsigned int>(region.x), static_cast<unsigned int>(region.y)});
    ImGui::Image(m_renderer->getTexture(), {region.x, region.y},  {0, 1}, {1, 0});
    m_rendererPosition = {ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y};
    ImGui::End();
}



SceneRender &SceneRender::operator=(const SceneRender &render)
{
    std::cout << render.m_renderer << std::endl;
    m_renderer = render.m_renderer;
    ref_engine = render.ref_engine;
    m_shader_renderer = render.m_shader_renderer;
    return *this;
}
