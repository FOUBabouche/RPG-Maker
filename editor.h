#ifndef EDITOR_H
#define EDITOR_H

#include "engineView.h"
#include "camera.h"

class Editor {
public:
	void Start();

	void Update(Engine& engine);
private:
	EngineView engineWin;
	Camera camera;
};

#endif