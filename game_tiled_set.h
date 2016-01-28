#ifndef GAMETILEDSET_H
#define GAMETILEDSET_H

#include <QPixmap>
#include <QVector>
#include "game_tile.h"

class GameTiledSet : public QPixmap
{
public:
    GameTiledSet();
    explicit GameTiledSet(QString filename,
                          int margin,
                          int space,
                          QSize tilesize,
                          int firstgid,
                          int tilecount);
    GameTile *getTile(int id);
    int TotalTiles();
private:
    void GenerateTiles();
    int margin;
    int spacing;
    QSize tilesize;
    int firstgid;
    int tilecount;
    QVector<GameTile> tiles;
};

#endif // GAMETILEDSET_H
