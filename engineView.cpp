#include "engineView.h"

#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

EngineView::EngineView()
{
	renderTexture = std::make_unique<sf::RenderTexture>(sf::Vector2u(800, 600));
}

sf::Vector2f EngineView::GetMousePos(Camera& camera) const
{
	return renderTexture.get()->mapPixelToCoords(sf::Vector2i(ImGui::GetMousePosOnOpeningCurrentPopup()), camera.GetView());
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

	ImGui::Begin("Scene");
	imageSize = ImGui::GetContentRegionAvail();
	renderTexture.get()->resize(imageSize);
	sf::Sprite sprite{ renderTexture.get()->getTexture() };
	ImGui::Image(renderTexture.get()->getTexture(), imageSize);
	ImGui::End();
}

