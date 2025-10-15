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
	Camera() = default;
	
	void SetZoom(float zoom);
	void SetPosition(sf::Vector2f position);

	sf::View GetView(void) const;
	float GetZoom(void) const;

	void Update(float dt);
	void SetRenderTarget(sf::RenderTexture& render, sf::Vector2f renderSize);
private:
	sf::View view;
	float m_zoom;
};

#endif