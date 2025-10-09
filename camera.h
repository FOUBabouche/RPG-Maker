#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/View.hpp>

class EngineView;
class Camera {
public:

	sf::View GetView(void) const;

	void Update(float dt);
	void SetRenderTarget(EngineView& target);
private:
	sf::View view;
};

#endif