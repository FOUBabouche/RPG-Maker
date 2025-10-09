#include "camera.h"
#include "engineView.h"

sf::View Camera::GetView(void) const
{
	return view;
}

void Camera::Update(float dt) {

}

void Camera::SetRenderTarget(EngineView& target)
{
	view = sf::View{ sf::FloatRect({0, 0}, {target.getAvailSize().x, target.getAvailSize().y})};
	target.getRender().get()->setView(view);
}
