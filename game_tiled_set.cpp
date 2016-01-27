#include "game_tiled_set.h"

#include <QtMath>

GameTiledSet::GameTiledSet()
{

}

GameTiledSet::GameTiledSet(QString filename,
                           int margin,
                           int space,
                           QSize tilesize)
{
    load(filename);
    this->margin = margin;
    this->spacing = space;
    this->tilesize = tilesize;
}

GameTile *GameTiledSet::getTile(int id)
{
    if(id >= tiles.size()) {
        return NULL;
    } else {
        GameTile *gtile = &tiles[id];
        return gtile;
    }
}

void GameTiledSet::GenerateTiles()
{
    int tx = tilesize.width();
    int ty = tilesize.height();
    for(int y=margin; y<this->height(); y+=(spacing + ty) ) {
        for(int x=margin; x<this->width(); x+=(spacing + tx) ) {
            GameTile tile;
            tile.addImage(this, QRect(x, y, tx, ty));
        }
    }
}
