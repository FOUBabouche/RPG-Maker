#ifndef __TILE_H__
#define __TILE_H__

#include <object.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <vector>

class Tile : public Object{
    public:
        Tile() = default;
        Tile(sf::Vector2f position, sf::Vector2f size);
        Tile(sf::Vector2f position, sf::Vector2f size, sf::IntRect uv, sf::Texture* texture);
        Tile(sf::Vector2f position, sf::Vector2f size, std::vector<sf::IntRect> uv, sf::Texture* texture);
        Tile(Tile& tile);
        Tile(const Tile& tile);
        ~Tile() = default;

        sf::Texture* getTextureRef(void) const;
        sf::IntRect getUV(void) const;
        std::vector<sf::IntRect> getUVs(void) const;

        void setTextureRef(sf::Texture* ref);
        void setUV(std::vector<sf::IntRect>& uv);

        void start() override;
        void update(float dt)override;
        void draw(sf::RenderTarget& target)override;
    public: // Operators
        Tile& operator=(Tile& tile);
        Tile& operator=(const Tile& tile);
        bool operator==(Tile& tile);
        bool operator!=(Tile& tile);
    private:
        sf::Texture* m_textureRef;
        std::vector<sf::IntRect> m_uvs;
        float animationSpeed = 1;
        float totalTime = 0;
        int currentUVIndex = 0;
};

#endif