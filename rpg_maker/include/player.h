#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <object.h>

class Player : public Object{
    public:
        Player() = default;
        Player(std::string _name);
        ~Player() = default;

    private:
        
};

#endif