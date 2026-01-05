#ifndef __TILEMAP_H__
#define __TILEMAP_H__

#include <object.h>
#include <tile.h>

#include <vector>

class TileMap : public Object{
    public:
        TileMap() = default;
        TileMap(std::string _name);
        TileMap(std::string _name, sf::Vector2u tileSize);
        TileMap(TileMap& tm);
        TileMap(const TileMap& tm);
        ~TileMap() = default;

        sf::Vector2u getTileSize(void) const;

        sf::Vector2u getCoordToGridPos(sf::Vector2f mousePos);

        void setTile(sf::Vector2u gridPosition, const Tile& tile);
        void removeTile(sf::Vector2u gridPosition);

        Tile* getTile(const sf::Vector2i& gridPos);
        bool tileIsHere(const sf::Vector2i& gridPos);

        void start() override {};
        void update(float dt) override;
        void draw(sf::RenderTarget& target) override;
        void drawGrid(sf::RenderTarget& target, sf::Vector2f cameraPos, sf::Vector2f renderSize, float zoom);

    public:
        TileMap& operator=(TileMap& tm);
        TileMap& operator=(const TileMap& tm);

    private:
        std::vector<std::vector<Tile>> m_tiles;
        sf::Vector2u m_tileSize;

};

#endif