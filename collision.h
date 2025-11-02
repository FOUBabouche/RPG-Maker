#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "tile.h"

class Collision {
public:
	bool AABB(Tile& tile, Player& player) const;
};

#endif
