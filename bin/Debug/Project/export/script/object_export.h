#ifndef __OBJECT_EXPORT_H__
#define __OBJECT_EXPORT_H__

#include <object.h>
#include <string>

#ifndef OBJECT_API
#define OBJECT_API extern "C" __declspec(dllexport)
#endif

OBJECT_API Object* CreateObject();
OBJECT_API void DestroyObject(Object* obj);
OBJECT_API char* GetNameObject(Object* obj);
OBJECT_API void StartObject(Object* obj);
OBJECT_API void UpdateObject(Object* obj, float dt);
OBJECT_API void DrawObject(Object* obj, sf::RenderTarget& target);

#endif