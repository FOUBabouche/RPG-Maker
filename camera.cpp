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

void Camera::SetPosition(sf::Vector2f position)
{
	view.setCenter(position);
}

void Camera::SetRenderTarget(sf::RenderTexture& render, sf::Vector2f renderSize)
{
	view.setSize(renderSize);
	render.setView(view);
}
