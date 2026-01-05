#include <tile.h>
#include <object.h>
#include <SFML/Graphics/RectangleShape.hpp>

Tile::Tile(sf::Vector2f _position, sf::Vector2f _size)
{
    currentUVIndex = 0;
    position = _position;
    size = _size;
    m_textureRef = nullptr;
}

Tile::Tile(sf::Vector2f _position, sf::Vector2f _size, sf::IntRect uv, sf::Texture *texture)
{
    currentUVIndex = 0;
    position = _position;
    size = _size;
    m_textureRef = texture;
    m_isFilled = true;
    m_uvs.push_back(uv);
}

Tile::Tile(sf::Vector2f _position, sf::Vector2f _size, std::vector<sf::IntRect> uv, sf::Texture *texture)
{
    currentUVIndex = 0;
    position = _position;
    size = _size;
    m_textureRef = texture;
    m_uvs = uv;
    m_isFilled = true;
}

Tile::Tile(Tile &tile)
{
    currentUVIndex = 0;
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uvs = tile.m_uvs;
    m_isFilled = tile.m_isFilled;
}

Tile::Tile(const Tile& tile){
    currentUVIndex = 0;
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uvs = tile.m_uvs;
    m_isFilled = tile.m_isFilled;
}

sf::Texture *Tile::getTextureRef(void) const
{
    return m_textureRef;
}

sf::IntRect Tile::getUV(void) const
{
    return m_uvs[currentUVIndex];
}

std::vector<sf::IntRect> Tile::getUVs(void) const
{
    return m_uvs;
}

bool Tile::isFilled(void) const
{
    return m_isFilled;
}

void Tile::setTextureRef(sf::Texture *ref)
{
    m_textureRef = ref;
}

void Tile::setUV(std::vector<sf::IntRect> &uv)
{
    m_uvs = uv;
}

void Tile::start()
{
    m_textureRef = nullptr;
}

void Tile::update(float dt)
{
    if(m_uvs.size()>0){
        if(totalTime >= 1 * animationSpeed){
            currentUVIndex++;
            if(currentUVIndex == m_uvs.size()){
                currentUVIndex = 0;
            }
            totalTime = 0;
        }else{ 
            totalTime += dt;
        }
    }
}

void Tile::draw(sf::RenderTarget& target)
{
    sf::RectangleShape shape(size);
    shape.setPosition(position);
    shape.setTexture(m_textureRef);
    if(m_uvs.size()>0)
        shape.setTextureRect(m_uvs[currentUVIndex]);

    target.draw(shape);
}

Tile &Tile::operator=(Tile &tile)
{
    currentUVIndex = 0;
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uvs = tile.m_uvs;
    m_isFilled = tile.m_isFilled;
    return *this;
}

Tile &Tile::operator=(const Tile &tile)
{
    currentUVIndex = 0;
    position = tile.position;
    size = tile.size;
    m_textureRef = tile.m_textureRef;
    m_uvs = tile.m_uvs;
    m_isFilled = tile.m_isFilled;
    return *this;
}

bool Tile::operator==(Tile &tile)
{
    return (
        position == tile.position &&
        size == tile.size &&
        m_textureRef == tile.m_textureRef &&
        m_uvs == tile.m_uvs &&
        m_isFilled != tile.m_isFilled
    );
}

bool Tile::operator!=(Tile &tile)
{
    return (
        position != tile.position &&
        size != tile.size &&
        m_textureRef != tile.m_textureRef &&
        m_uvs != tile.m_uvs &&
        m_isFilled != tile.m_isFilled
    );
}
