#ifndef EDITOR_H
#define EDITOR_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "engineView.h"
#include "camera.h"

#include <SFML/Graphics/Texture.hpp>
#include <optional>

class Editor {
public:
	void Start();

	void Event(std::optional<sf::Event> event);
	void Update(Engine& engine);
private:
	EngineView engineWin;
	Camera camera;
	sf::Texture placeHolder;
	bool leftPressed = false;
	bool rightPressed = false;
};

#endif