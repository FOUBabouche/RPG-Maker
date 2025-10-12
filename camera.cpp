#include "camera.h"
#include "engineView.h"

sf::View Camera::GetView(void) const
{
	return view;
}

void Camera::Update(float dt) {

}

void Camera::SetRenderTarget(sf::RenderTexture& render, sf::Vector2f renderSize)
{
	view = sf::View{ sf::FloatRect({0, 0}, {renderSize.x, renderSize.y})};
	render.setView(view);
}
