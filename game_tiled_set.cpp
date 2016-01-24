#include "game_tiled_set.h"

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
    this->space = space;
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
    QPixmap pmx = TilesetImage();
    int margin = map->tileset.margin;
    int spacing = map->tileset.spacing;
    int tx = map->tilewidth;
    int ty = map->tileheight;

    int px = margin + (spacing + tx)*x;
    int py = margin + (spacing + ty)*y;
    QPixmap tile = pmx.copy(px, py, tx, ty);
    return tile;
}
