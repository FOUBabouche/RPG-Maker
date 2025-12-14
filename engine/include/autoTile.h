#ifndef __AUTO_TILE_H__
#define __AUTO_TILE_H__

#include <filesystem>
#include <tilemap.h>
#include <unordered_map>

class AutoTile{
    public:
        AutoTile() = default;
        AutoTile(const std::filesystem::path& texturePath);
        ~AutoTile() = default;

        unsigned int getMask(TileMap*& tilemap, sf::Vector2i gridPos);

        void addTile(TileMap*& tilemap, sf::Vector2i gridPos);
    private:
        sf::Texture* texture;
        std::unordered_map<unsigned int, sf::Vector2i> possibilities = {
            {0b0000, {3, 3}},
            {0b0001, {0, 3}},
            {0b0010, {2, 3}},
            {0b0011, {1, 3}},
            {0b0100, {3, 2}},
            {0b0101, {0, 2}},
            {0b0110, {2, 2}},
            {0b0111, {1, 2}},
            {0b1000, {3, 0}},
            {0b1001, {0, 0}},
            {0b1010, {2, 0}},
            {0b1011, {1, 0}},
            {0b1100, {3, 1}},
            {0b1101, {0, 1}},
            {0b1110, {2, 1}},
            {0b1111, {1, 1}}
        };
};

#endif