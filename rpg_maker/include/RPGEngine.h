#ifndef __RPG_ENGINE_H__
#define __RPG_ENGINE_H__

#include <engine.h>

class RPGEngine : public Engine{
    public:
        RPGEngine() =default;
        ~RPGEngine() = default;

        void start() override;
        void update(float dt) override;
};

#endif