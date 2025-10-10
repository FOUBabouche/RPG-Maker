#ifndef CAMERA_H
#define CAMERA_H

#ifndef SFML_STATIC
#define SFML_STATIC
#endif

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