#include "core.h"
#include <imgui-SFML.h>
#include <imgui.h>

sf::RenderWindow Core::window;
sf::Clock Core::deltaClock;

void Core::Init() {
    Start();
    while (window.isOpen()) {
        Event();
        Update();
        Render();
    }
}

void Core::Start()
{
	window.create(sf::VideoMode({ 800, 600 }), "RPG Maker");
	ImGui::SFML::Init(window);
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
    ImGui::SFML::Update(window, deltaClock.restart());
}

void Core::Render() {
    window.clear();

    ImGui::SFML::Render(window);
    window.display();
}