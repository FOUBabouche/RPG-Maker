#include "core.h"
#include <imgui-SFML.h>
#include <imgui.h>

#include "editor.h"
#include "engine.h"

sf::RenderWindow Core::window;
sf::Clock Core::deltaClock;
float Core::deltaTime = 0;

Editor editor;
Engine engine;

void Core::Init() {
    Start();
    while (window.isOpen()) {
        Event();
        Update();
        Render();
    }
    ImGui::SFML::Shutdown();
}

void Core::Start()
{
	window.create(sf::VideoMode({ 800, 600 }), "RPG Maker");
	ImGui::SFML::Init(window);

    engine.Start();
    editor.Start();
}

void Core::Event()
{
    while (const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        if (event->is<sf::Event::Closed>())
            window.close();
        engine.Event(event);
    }
}

void Core::Update()
{
    sf::Time time = deltaClock.restart();
    deltaTime = time.asSeconds();


    ImGui::SFML::Update(window, time);

    engine.Update(deltaTime);
    editor.Update(engine);
}

void Core::Render() {
    window.clear();

    ImGui::SFML::Render(window);
    window.display();
}