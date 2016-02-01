#include "map/game_tiled_set.h"

#include <QtMath>

#include "map/game_tile.h"

GameTiledSet::GameTiledSet()
{

}

GameTiledSet::~GameTiledSet()
{
    for(int i=0; i<tiles.size(); i++)
        delete tiles.at(i);
}

GameTiledSet::GameTiledSet(QString name,
                           int margin,
                           int space,
                           QSize tilesize,
                           int firstgid,
                           int tilecount)
{
    this->name = name;
    this->margin = margin;
    this->spacing = space;
    this->tilesize = tilesize;
    this->firstgid = firstgid;
    this->tilecount = tilecount;
}

void GameTiledSet::LoadFilename(QString filename)
{
    load(filename);
    GenerateTiles();
}

GameTile *GameTiledSet::getTile(int id)
{
    if(id >= tiles.size() || id < 0) {
        return NULL;
    } else {
        GameTile *gtile = tiles.at(id);
        return gtile;
    }
}

int GameTiledSet::TotalTiles()
{
    return tiles.size();
}

int GameTiledSet::FirstGid()
{
    return firstgid;
}

void GameTiledSet::GenerateTiles()
{
    int tx = tilesize.width();
    int ty = tilesize.height();
    int id = 0;
    for(int y=margin; y<this->height(); y+=(spacing + ty) ) {
        for(int x=margin; x<this->width(); x+=(spacing + tx) ) {
            GameTile *tile = new GameTile(id++);
            tile->addImage(this, QRect(x, y, tx, ty));
            tiles.push_back(tile);
        }
    }
}
