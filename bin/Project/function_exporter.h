#pragma once

#include <object.h>

#define CREATEOBJECT(NAME) extern "C" __declspec(dllexport) Object* create ## NAME(){ \
                                                                        return new (NAME);  \
                                                                    };\

extern "C" __declspec(dllexport) void deleteObject(Object* object);
extern "C" __declspec(dllexport) void start(Object* object);
extern "C" __declspec(dllexport) void update(Object* object, float dt);
extern "C" __declspec(dllexport) void render(Object* object, sf::RenderTarget& target);