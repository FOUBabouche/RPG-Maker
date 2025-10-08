#include "core.h"
#include <imgui-SFML.h>
#include <imgui.h>

#include "editor.h"

sf::RenderWindow Core::window;
sf::Clock Core::deltaClock;

Grid grid{ {16, 16} };

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
    grid.SetTile({ 0, 0 }, sf::Color::Red, nullptr);
    grid.SetTile({ 4, 0 }, sf::Color::Blue, nullptr);
    grid.SetTile({ 3, 0 }, sf::Color::Green, nullptr);
    grid.SetTile({ 0, 0 }, sf::Color::Green, nullptr);
    grid.RemoveTile({ 4, 0 });
    grid.RemoveTile({4, 0});
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

    grid.DrawGrid(window);
    grid.Draw(window);

    ImGui::SFML::Render(window);
    window.display();
}