#include "engineView.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <iostream>

EngineView::EngineView()
{
	renderTexture = std::make_unique<sf::RenderTexture>(sf::Vector2u(800, 600));
}

void EngineView::Draw(Engine& engine) {
	renderTexture.get()->clear(sf::Color::Black);
	engine.Render(*renderTexture.get());
	renderTexture.get()->display();

	ImGui::Begin("Scene");
	renderTexture.get()->resize({ ImGui::GetContentRegionAvail() });
	ImGui::Image(renderTexture.get()->getTexture());
	ImGui::End();
}

