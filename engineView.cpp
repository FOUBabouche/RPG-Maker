#include "engineView.h"

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

EngineView::EngineView()
{
	renderTexture = std::make_unique<sf::RenderTexture>(sf::Vector2u(800, 600));
}

// Sans le zoom de la cam
sf::Vector2f EngineView::GetMousePos(sf::Vector2f cameraPosition, sf::Vector2f cameraSize, float zoom) const
{
	ImVec2 windowMousePos = ImGui::GetMousePos();
	// RenderPos = renderPos = ImGui::GetItemRectMin();
	// on le mets en dessous du ImGui::Image(...);
	sf::Vector2f renderLocalPos = { windowMousePos.x - renderPos.x, windowMousePos.y - renderPos.y };

	return (renderLocalPos + (cameraPosition - sf::Vector2f(cameraSize.x / 2, cameraSize.y / 2))) / zoom;
}

std::unique_ptr<sf::RenderTexture>& EngineView::getRender(void)
{
	return renderTexture;
}

bool EngineView::isHover(void) const
{
	return renderIsHovered;
}

sf::Vector2f EngineView::getRenderPos()
{
	return renderPos;
}

sf::Vector2f EngineView::getAvailSize()
{
	return imageSize;
}

void EngineView::Draw(Engine& engine, Camera& camera) {
	renderTexture.get()->clear(sf::Color::Black);
	engine.Render(*renderTexture.get(), camera);
	renderTexture.get()->display();

	

	if (ImGui::Begin("Scene", 0, flags)) {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("play")) {

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Separator();
		imageSize = ImGui::GetContentRegionAvail();
		renderTexture.get()->resize(imageSize);
		sf::Sprite sprite{ renderTexture.get()->getTexture() };
		ImGui::Image(renderTexture.get()->getTexture(), imageSize);
		renderIsHovered = ImGui::IsItemHovered();
		if (renderIsHovered) {
			flags = ImGuiWindowFlags_NoMove;
		}
		else flags = 0;
		renderPos = ImGui::GetItemRectMin();
		ImGui::End();
	}
	
}

