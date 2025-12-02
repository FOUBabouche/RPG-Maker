#ifndef __OBJECT_PUGLIN_H__
#define __OBJECT_PUGLIN_H__

#include <windows.h>

#include <object.h>

typedef Object* (*CreateFunc)();
typedef void (*DeleteFunc)(Object*);
typedef char* (*GetNameFunc)(Object*);
typedef void (*StartFunc)(Object*);
typedef void (*UpdateFunc)(Object*, float);
typedef void (*DrawFunc)(Object*, sf::RenderTarget&);

struct ObjectPlugin
{
    HMODULE dll;
    CreateFunc createObject;
    DeleteFunc deleteObject;
    GetNameFunc getNameObject;
    StartFunc startObject;
    UpdateFunc updateObject;
    DrawFunc drawObject;
};


#endif