#ifndef CORE_H
#define CORE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

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
};

#endif