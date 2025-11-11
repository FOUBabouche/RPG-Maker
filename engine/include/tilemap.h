#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <object.h>
#include <tile.h>

#include <vector>

class TileMap : public Object{
    public:
        TileMap() = default;
        TileMap(TileMap& tm);
        TileMap(const TileMap& tm);
        ~TileMap() = default;

        sf::Vector2u getCoordToGridPos(sf::Vector2f mousePos);

        void setTile(sf::Vector2u gridPosition, Tile& tile);
        void removeTile(sf::Vector2u gridPosition);

        void draw(sf::RenderTarget& target) override;

    public:
        TileMap& operator=(TileMap& tm);
        TileMap& operator=(const TileMap& tm);

    private:
        std::vector<std::vector<Tile>> m_tiles;
        sf::Vector2u m_tileSize;

};

#endif