#ifndef EDITOR_H
#define EDITOR_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include "engineView.h"
#include "camera.h"

#include <SFML/Graphics/Texture.hpp>

class Editor {
public:
	void Start();

	void Update(Engine& engine);
private:
	EngineView engineWin;
	Camera camera;
	sf::Texture placeHolder;
};

#endif