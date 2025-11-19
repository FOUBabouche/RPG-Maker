#ifndef __TILE_SELECTOR_H__
#define __TILE_SELECTOR_H__

#include <element.h>
#include <brush.h>
#include <fileContener.hpp>

#include <SFML/Graphics/Texture.hpp>

class TileSelector : public Element{
    public:
        TileSelector() = default;
        TileSelector(std::string _name);
        ~TileSelector() = default;

        void setBrush(Brush* brush);
    
        void update() override;
    private:
        Brush* m_brushRef;
        FileContener textureContener;
        std::filesystem::path curentTexturePath;
};

#endif