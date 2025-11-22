#ifndef __BRUSH_PANEL_H__
#define __BRUSH_PANEL_H__

#include <element.h>
#include <brush.h>
#include <tile.h>

#include <vector>

enum class TILE_TYPE{
    NORMAL_TILE,
    ANIMATED_TILE,
    COLLISION_TILE,
    TRANSPARENT_TILE
};

class BrushPanel : public Element{
    public:
        BrushPanel() = default;
        BrushPanel(std::string _name, Base_Editor* editor);
        ~BrushPanel();

        Brush& getBrush(void);
        Tile& currentAnimatedTile(void);
        TILE_TYPE getTileType(void) const;

        void addAnimatedTile(const Tile& tile);

        void update(float dt) override;
    private:
        Brush brush;
        TILE_TYPE tileType = TILE_TYPE::NORMAL_TILE;
        Tile currentAnimatedTileSelected;
        std::vector<Tile> animatedTiles;
};

#endif