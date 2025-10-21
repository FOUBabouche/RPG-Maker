#ifndef PAINT_H
#define PAINT_H

#include "brush.h"

class Paint : Brush {
public:
	Paint() = default;

	void click() override {
		return; // Code...
	}
};

#endif