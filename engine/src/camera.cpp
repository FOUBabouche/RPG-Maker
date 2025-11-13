#include <camera.h>

Camera::Camera()
{
    name = "Camera";
    position = {0, 0};
    m_zoom = 1;
}

Camera::Camera(std::string _name)
{
    name = _name;
    position = {0, 0};
    m_zoom = 1;
}

Camera::Camera(std::string _name, sf::Vector2f _position)
{
    name = _name;
    position = _position;
    m_zoom = 1;
}

void Camera::setZoom(float zoom)
{
    m_zoom = zoom;
}

float Camera::getZoom(void) const
{
    return m_zoom;
}

void Camera::update(float dt)
{
    m_handle.setSize(size);
    m_handle.setCenter(position);
    m_handle.zoom(m_zoom);
}

void Camera::draw(sf::RenderTarget &target)
{
    size = static_cast<sf::Vector2f>(target.getSize());
    target.setView(m_handle);
}
