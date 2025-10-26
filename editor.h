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
	void Start(Engine& engine);

	void Event(std::optional<sf::Event> event);
	void Update(Engine& engine, float deltaTime);

	void SaveScene(Engine& engine, std::string fileName);
	void LoadScene(Engine& engine, std::string fileName);

	bool AlreadyhaveThisTexture(std::string textureName);
	sf::Texture* GetTextureByName(std::string textureName);

private:
	// Other
	EngineView engineWin;
	Camera camera;
	sf::Vector2f lastMousePos;
	float zoom = 3;
	Tools tool;
	Brush brush;
	float* col;
	unsigned int currentGridSelected = 0;
	bool leftPressed = false;
	bool rightPressed = false;
	bool canBeANewPos = true;

	bool brushWinIsOpen = false;
	bool selectTextureWinIsOpen = false;
	bool selectLayerWinIsOpen = false;

	std::string currentTexturePath;
	std::vector<sf::Texture*> textures;
	std::vector<std::string> texturesPaths;
	sf::Texture* currentTexture;

private:
	sf::Texture* placeHolder;
	// UI
	sf::Texture* importButton;
	sf::Texture* saveButton;
	sf::Texture* moveButton;
	sf::Texture* paintButton;
	sf::Texture* eraseButton;
	sf::Texture* textureButton;
	sf::Texture* addLayerButton;
	sf::Texture* selectLayerButton;
};

#endif