#include <tile.h>
#include <SFML/Graphics/RectangleShape.hpp>

Tile::Tile(Tile &tile)
{
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uv = tile.m_uv;
}

sf::Texture *Tile::getTextureRef(void) const
{
    return m_textureRef;
}

sf::IntRect Tile::getUV(void) const
{
    return m_uv;
}

void Tile::setTextureRef(sf::Texture *ref)
{
    m_textureRef = ref;
}

void Tile::setUV(sf::IntRect &uv)
{
    m_uv = uv;
}

void Tile::Start()
{
    m_textureRef = nullptr;
}

void Tile::Update()
{

}

void Tile::Draw(sf::RenderTarget& target)
{
    sf::RectangleShape shape(size);
    shape.setPosition(position);
    shape.setTexture(m_textureRef);
    shape.setTextureRect(m_uv);

    target.draw(shape);
}

Tile &Tile::operator=(Tile &tile)
{
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uv = tile.m_uv;
    return *this;
}

bool Tile::operator==(Tile &tile)
{
    return (
        position == tile.position &&
        size == tile.size &&
        m_textureRef == tile.m_textureRef &&
        m_uv == tile.m_uv
    );
}

bool Tile::operator!=(Tile &tile)
{
    return (
        position != tile.position &&
        size != tile.size &&
        m_textureRef != tile.m_textureRef &&
        m_uv != tile.m_uv
    );
}
