#ifndef EDITOR_H
#define EDITOR_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "engineView.h"
#include "camera.h"

#include <SFML/Graphics/Texture.hpp>
#include <optional>

enum Tools {
	Move,
	Paint,
	Erase
};

class Editor {
public:
	void Start();

	void Event(std::optional<sf::Event> event);
	void Update(Engine& engine, float deltaTime);
private:
	EngineView engineWin;
	Camera camera;
	float zoom = 1;
	Tools tool;
	bool leftPressed = false;
	bool rightPressed = false;

private:
	sf::Texture placeHolder;
	sf::Texture moveButton;
};

#endif