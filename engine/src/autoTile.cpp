#include <autoTile.h>

AutoTile::AutoTile(const std::filesystem::path& texturePath){
    texture = new sf::Texture(texturePath);
}

unsigned int AutoTile::getMask(TileMap*& tilemap, sf::Vector2i gridPos){
    unsigned int mask = 0;
    if(tilemap->getTile({gridPos.x+1, gridPos.y})) mask |= 0b0001; // Right
    if(tilemap->getTile({gridPos.x-1, gridPos.y})) mask |= 0b0010; // Left
    if(tilemap->getTile({gridPos.x, gridPos.y-1})) mask |= 0b0100; // Up
    if(tilemap->getTile({gridPos.x, gridPos.y+1})) mask |= 0b1000; // Down
    return mask;
}

void AutoTile::addTile(TileMap*& tilemap, sf::Vector2i gridPos){
    auto mask = getMask(tilemap, gridPos);
    auto uvPos = possibilities[mask];
    tilemap->setTile(static_cast<sf::Vector2u>(gridPos), {
        {gridPos.x*16.f, gridPos.y*16.f},
        {16, 16},
        {uvPos * 16, {16, 16}},
        texture
    });
}