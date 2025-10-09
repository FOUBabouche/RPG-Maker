#ifndef ENGINE_VIEW_H
#define ENGINE_VIEW_H

#include "engine.h"
#include "camera.h"

#include <imgui-SFML.h>
#include <imgui.h>
#include <memory>

class EngineView {
public:
	EngineView();

	sf::Vector2f GetMousePos(Camera& camera) const;

	std::unique_ptr<sf::RenderTexture>& getRender(void);

	sf::Vector2f getAvailSize();

	void Draw(Engine& engine, Camera& camera);
private:
	std::unique_ptr<sf::RenderTexture> renderTexture;
	ImVec2 imageSize;
	ImVec2 renderPos;
};

#endif