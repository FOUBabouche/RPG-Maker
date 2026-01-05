#pragma once

#include <object.h>

class Player : public Object {
public:
	void start() override;
	void update(float dt) override;
	void draw(sf::RenderTarget& target) override;
};

