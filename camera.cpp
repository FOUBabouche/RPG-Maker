#include "camera.h"
#include "engineView.h"

sf::View Camera::GetView(void) const
{
	return view;
}

float Camera::GetZoom(void) const
{
	return m_zoom;
}

void Camera::SetZoom(float zoom)
{
	m_zoom = zoom;
}

void Camera::Update(float dt) {
	view.zoom(m_zoom);
}

void Camera::SetRenderTarget(sf::RenderTexture& render, sf::Vector2f renderSize)
{
	view = sf::View{ sf::FloatRect({0, 0}, {renderSize.x, renderSize.y})};
	render.setView(view);
}
