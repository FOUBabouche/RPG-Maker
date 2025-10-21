#ifndef CORE_H
#define CORE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "editor.h"
#include "engine.h"

class Core {
public:
	Core();
	void Start();
	void Event();
	void Update();
	void Render();
private:
	sf::RenderWindow window;
	sf::Clock deltaClock;
	float deltaTime;

	Editor editor;
	Engine engine;
};

#endif