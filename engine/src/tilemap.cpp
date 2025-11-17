#include <tilemap.h>
#include <cmath>

TileMap::TileMap(std::string _name)
{
	name = _name;
	position = {0, 0};
	m_tileSize = {16, 16};
}

TileMap::TileMap(std::string _name, sf::Vector2u tileSize)
{
	name = _name;
	position = {0, 0};
	m_tileSize = {16, 16};
	m_tileSize = tileSize;
}

TileMap::TileMap(TileMap &tm)
{
	name = tm.name;
	position = tm.position;
    size = tm.size;
	m_tiles = tm.m_tiles;
	m_tileSize = tm.m_tileSize;
}

TileMap::TileMap(const TileMap& tm){
	name = tm.name;
	position = tm.position;
    size = tm.size;
	m_tiles = tm.m_tiles;
	m_tileSize = tm.m_tileSize;
}

sf::Vector2u TileMap::getTileSize(void) const
{
    return m_tileSize;
}

sf::Vector2u TileMap::getCoordToGridPos(sf::Vector2f mousePos)
{
	return sf::Vector2u(std::floor(mousePos.x /  m_tileSize.x), std::floor(mousePos.y / m_tileSize.y));
}

void TileMap::setTile(sf::Vector2u gridPosition, const Tile &tile)
{
	if (m_tiles.size() <= gridPosition.x) m_tiles.resize(gridPosition.x + 1);
	if (m_tiles[gridPosition.x].size() <= gridPosition.y) m_tiles[gridPosition.x].resize(gridPosition.y + 1);

	m_tiles[gridPosition.x][gridPosition.y] = tile;
}

void TileMap::removeTile(sf::Vector2u gridPosition)
{
    if (gridPosition.x >= m_tiles.size() || gridPosition.y >= m_tiles[gridPosition.x].size())return;

	Tile tilePtr = m_tiles[gridPosition.x][gridPosition.y];
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

void TileMap::draw(sf::RenderTarget &target)
{
	for (auto&& x : m_tiles)
		for(auto&& y : x)
			y.draw(target);
}

TileMap &TileMap::operator=(TileMap &tm)
{
	name = tm.name;
	position = tm.position;
    size = tm.size;
	m_tiles = tm.m_tiles;
	m_tileSize = tm.m_tileSize;
	return *this;
}

TileMap& TileMap::operator=(const TileMap& tm){
	name = tm.name;
	position = tm.position;
    size = tm.size;
	m_tiles = tm.m_tiles;
	m_tileSize = tm.m_tileSize;
	return *this;
}