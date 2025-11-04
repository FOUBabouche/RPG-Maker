#ifndef __CORE_H__
#define __CORE_H__

#include <RPGEngine.h>
#include <editor.h> 

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <memory>

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

	std::unique_ptr<RPGEngine> engine;
	std::unique_ptr<Editor> editor;
};

#endif