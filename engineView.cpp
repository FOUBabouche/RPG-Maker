#include "engineView.h"

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

EngineView::EngineView()
{
	renderTexture = std::make_unique<sf::RenderTexture>(sf::Vector2u(800, 600));
}

// Sans le zoom de la cam
sf::Vector2f EngineView::GetMousePos(Camera& camera) const
{
	if (renderIsHovered) {
		sf::Vector2f viewPortPos = camera.GetView().getViewport().position;
		ImVec2 windowMousePos = ImGui::GetMousePos();
		// RenderPos = renderPos = ImGui::GetItemRectMin();
		// on le mets en dessous du ImGui::Image(...);
		ImVec2 renderLocalPos = { windowMousePos.x - renderPos.x, windowMousePos.y - renderPos.y };

		return { renderLocalPos.x + viewPortPos.x, renderLocalPos.y + viewPortPos.y };
	}
	return sf::Vector2f();
}

std::unique_ptr<sf::RenderTexture>& EngineView::getRender(void)
{
	return renderTexture;
}

sf::Vector2f EngineView::getAvailSize()
{
	return imageSize;
}

void EngineView::Draw(Engine& engine, Camera& camera) {
	renderTexture.get()->clear(sf::Color::Black);
	engine.Render(*renderTexture.get(), camera);
	renderTexture.get()->display();

	ImGuiWindowFlags flags = 0;

	ImGui::Begin("Scene", 0, flags);
	imageSize = ImGui::GetContentRegionAvail();
	renderTexture.get()->resize(imageSize);
	sf::Sprite sprite{ renderTexture.get()->getTexture() };
	ImGui::Image(renderTexture.get()->getTexture(), imageSize);
	renderIsHovered = ImGui::IsItemHovered();
	if (renderIsHovered) {
		flags |= ImGuiWindowFlags_NoMove;
	}
	else flags = 0;
	renderPos = ImGui::GetItemRectMin();
	ImGui::End();
}

