#ifndef CORE_H
#define CORE_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class Core {
public:
	static void Init();
	static void Start();
	static void Event();
	static void Update();
	static void Render();
private:
	static sf::RenderWindow window;
	static sf::Clock deltaClock;
};

#endif