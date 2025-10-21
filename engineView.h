#ifndef ENGINE_VIEW_H
#define ENGINE_VIEW_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "engine.h"
#include "camera.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>

class EngineView {
public:
	EngineView();

	sf::Vector2f GetMousePos(sf::Vector2f cameraPos, sf::Vector2f cameraSize, float zoom) const;

	std::unique_ptr<sf::RenderTexture>& getRender(void);
	bool isHover(void) const;

	sf::Vector2f getRenderPos();
	sf::Vector2f getAvailSize();

	void Draw(Engine& engine, Camera& camera);
private:
	std::unique_ptr<sf::RenderTexture> renderTexture;
	ImVec2 imageSize;
	ImVec2 renderPos;

	ImGuiWindowFlags flags = 0;
	bool renderIsHovered;
};

#endif