#include <tilemap.h>
#include <cmath>

sf::Vector2u TileMap::getCoordToGridPos(sf::Vector2f mousePos)
{
	return sf::Vector2u(std::floor(mousePos.x / .x), std::floor(mousePos.y / m_tileSize.y));
}

void TileMap::SetTile(sf::Vector2u gridPosition, Tile &tile)
{
    if (gridPosition.x < 0 || gridPosition.y < 0) return;

	
	if (m_tiles.size() <= gridPosition.x) m_tiles.resize(gridPosition.x + 1);
	if (m_tiles[gridPosition.x].size() <= gridPosition.y) m_tiles[gridPosition.x].resize(gridPosition.y + 1);

	m_tiles[gridPosition.x][gridPosition.y] = tile;
}

void TileMap::RemoveTile(sf::Vector2u gridPosition)
{
    if (gridPosition.x >= m_tiles.size() || gridPosition.y >= m_tiles[gridPosition.x].size())return;

	auto& tilePtr = m_tiles[gridPosition.x][gridPosition.y];
	if (tilePtr.position == sf::Vector2f(gridPosition.x * tilePtr.size.x, gridPosition.y * tilePtr.size.x)) {
		tilePtr = (Tile&)Tile();
		bool empty = true;
		for (auto& t : m_tiles[position.x]) {
			if (t != (Tile&)Tile()) { empty = false; break; }
		}
		if (empty) {
			m_tiles[position.x].clear();
		}
		return;
	}
}

void TileMap::Draw(sf::RenderTarget &target)
{
	for (auto&& x : m_tiles)
		for(auto&& y : x)
			y.Draw(target);
}
