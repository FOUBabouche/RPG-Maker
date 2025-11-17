#ifndef __BRUSH_PANEL_H__
#define __BRUSH_PANEL_H__

#include <element.h>
#include <brush.h>

enum class TILE_TYPE{
    NORMAL_TILE,
    ANIMATED_TILE,
    COLLISION_TILE,
    TRANSPARENT_TILE
};

class BrushPanel : public Element{
    public:
        BrushPanel() = default;
        BrushPanel(std::string _name);
        ~BrushPanel();

        Brush& getBrush(void);

        void update() override;
    private:
        Brush brush;
        TILE_TYPE tileType = TILE_TYPE::NORMAL_TILE;
        sf::Texture* placeHolder;
};

#endif