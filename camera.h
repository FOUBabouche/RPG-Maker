#ifndef CAMERA_H
#define CAMERA_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

class EngineView;
class Camera {
public:
	sf::View GetView(void) const;

	void Update(float dt);
	void SetRenderTarget(sf::RenderTexture& render, sf::Vector2f renderSize);
private:
	sf::View view;
};

#endif