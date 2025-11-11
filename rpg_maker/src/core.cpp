#include <core.h>
#include <imgui-SFML.h>
#include <imgui.h>


Core::Core(){
    Start();
    while (window.isOpen()) {
        Event();
        Update();
        Render();
    }
    delete editor;
    delete engine;
    ImGui::SFML::Shutdown();
}

void Core::Start()
{
	window.create(sf::VideoMode({ 800, 600 }), "RPG Maker");
	ImGui::SFML::Init(window);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    engine = new RPGEngine;
    engine->start();
    editor = new Editor(engine);
    editor->start();
}

void Core::Event()
{
    while (const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Core::Update()
{
    sf::Time time = deltaClock.restart();
    deltaTime = time.asSeconds();
    ImGui::SFML::Update(window, time);

    
    ImGui::DockSpaceOverViewport(0U, ImGui::GetMainViewport());

    engine->update(deltaTime);
    editor->update(deltaTime);
}

void Core::Render() 
{
    window.clear();
    ImGui::SFML::Render(window);
    window.display();
}