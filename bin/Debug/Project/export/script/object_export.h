#ifndef __OBJECT_EXPORT_H__
#define __OBJECT_EXPORT_H__

#include <object.h>

#ifdef OBJECT_EXPORTS
#define OBJECT_API extern "C" __declspec(dllexport)
#else
#define OBJECT_API extern "C" __declspec(dllimport)
#endif

extern "C" __declspec(dllexport) Object* CreateObject();
extern "C" __declspec(dllexport) void DestroyObject(Object* obj);

#endif