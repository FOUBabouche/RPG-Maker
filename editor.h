#ifndef EDITOR_H
#define EDITOR_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "engineView.h"
#include "camera.h"
#include "brush.h"

#include <SFML/Graphics/Texture.hpp>
#include <optional>

enum Tools {
	Move,
	Paint,
	Erase
};

class Editor {
public:
	Editor();
	~Editor();
	void Start();

	void Event(std::optional<sf::Event> event);
	void Update(Engine& engine, float deltaTime);
private:
	// Other
	EngineView engineWin;
	Camera camera;
	sf::Vector2f lastMousePos;
	float zoom = 1;
	Tools tool;
	Brush brush;
	float* col;
	bool leftPressed = false;
	bool rightPressed = false;
	bool canBeANewPos = true;

	bool brushWinIsOpen = false;
	bool selectTextureWinIsOpen = false;

	std::string currentTexturePath;
	std::vector<std::string> texturesPaths;
	sf::Texture* currentTexture;

private:
	// UI
	sf::Texture* placeHolder;
	sf::Texture* moveButton;
	sf::Texture* paintButton;
	sf::Texture* eraseButton;
	sf::Texture* textureButton;
};

#endif