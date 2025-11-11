#ifndef __TILE_H__
#define __TILE_H__

#include <object.h>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

class Tile : public Object{
    public:
        Tile() = default;
        Tile(sf::Vector2f position, sf::Vector2f size);
        Tile(Tile& tile);
        Tile(const Tile& tile);
        ~Tile() = default;

        sf::Texture* getTextureRef(void) const;
        sf::IntRect getUV(void) const;

        void setTextureRef(sf::Texture* ref);
        void setUV(sf::IntRect& uv);

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
        sf::IntRect m_uv;
};

#endif