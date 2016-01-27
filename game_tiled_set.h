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
                          QSize tilesize);
    GameTile *getTile(int id);
private:
    int margin;
    int spacing;
    QSize tilesize;
    void GenerateTiles();
    QVector<GameTile> tiles;
};

#endif // GAMETILEDSET_H
