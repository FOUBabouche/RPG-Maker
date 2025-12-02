#include <Player.h>
#include "object_export.h"
OBJECT_API Object* CreateObject() { return new Player(); }
OBJECT_API void DestroyObject(Object* obj) { delete obj; }
OBJECT_API char* GetNameObject(Object* obj) { return (char*)obj->name.c_str(); }
OBJECT_API void StartObject(Object* obj) { obj->start(); }
OBJECT_API void UpdateObject(Object* obj, float dt) { obj->update(dt); }
OBJECT_API void DrawObject(Object* obj, sf::RenderTarget& target) { obj->draw(target); }
