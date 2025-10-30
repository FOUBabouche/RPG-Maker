#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <object.h>
#include <vector>
#include <tile.h>

class TileMap : public Object{
    public:
        TileMap() = default;
        ~TileMap() = default;

        sf::Vector2u getCoordToGridPos(sf::Vector2f mousePos);

        void SetTile(sf::Vector2u gridPosition, Tile& tile);
        void RemoveTile(sf::Vector2u gridPosition);

        void Draw(sf::RenderTarget& target) override;

    private:
        std::vector<std::vector<Tile>> m_tiles;
        sf::Vector2u m_tileSize;

};

#endif