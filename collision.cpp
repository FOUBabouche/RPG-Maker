#include "collision.h"

bool Collision::AABB(Tile& tile, Player& player) const
{
	std::cout << '{' << tile.GetPosition().x << ", " << tile.GetPosition().y << "} "
			  << '{' << tile.GetPosition().x * tile.GetSize().x << ", " << tile.GetPosition().y * tile.GetSize().y << '}' << std::endl;

	std::cout << '{' << tile.GetPosition().x << ", " << tile.GetPosition().y << "} "
			  << '{' << tile.GetPosition().x * tile.GetSize().x << ", " << tile.GetPosition().y * tile.GetSize().y << '}' << std::endl;

	return (tile != (Tile&)Tile() ? (tile.GetPosition().x * tile.GetSize().x < player.getPosition().x + player.getSize().x &&
			(tile.GetPosition().x + tile.GetSize().x) * tile.GetSize().x > player.getPosition().x &&
			tile.GetPosition().y * tile.GetSize().y < player.getPosition().y + player.getSize().y &&
			(tile.GetPosition().y + tile.GetSize().y) * tile.GetSize().y > player.getPosition().y) : false);
}
