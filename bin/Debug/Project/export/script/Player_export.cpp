#include <Player.h>
#include "object_export.h"
OBJECT_API Object* CreateObject() { return new Player(); }
OBJECT_API void DestroyObject(Object* obj) { delete obj; }
