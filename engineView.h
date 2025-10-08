#ifndef ENGINE_VIEW_H
#define ENGINE_VIEW_H

#include "engine.h"
#include <memory>

class EngineView {
public:
	EngineView();

	void Draw(Engine& engine);
private:
	std::unique_ptr<sf::RenderTexture> renderTexture;
};

#endif