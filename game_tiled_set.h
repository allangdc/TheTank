#ifndef GAMETILEDSET_H
#define GAMETILEDSET_H

#include <QPixmap>
#include <QVector>
#include "game_tile.h"

class GameTiledSet : public QPixmap
{
public:
    GameTiledSet();
    virtual ~GameTiledSet();
    explicit GameTiledSet(QString name,
                          int margin,
                          int space,
                          QSize tilesize,
                          int firstgid,
                          int tilecount);
    void LoadFilename(QString filename);
    GameTile *getTile(int id);
    int TotalTiles();
    int FirstGid();
private:
    void GenerateTiles();
    int margin;
    int spacing;
    QSize tilesize;
    int firstgid;
    int tilecount;
    QString name;
    QVector<GameTile *> tiles;
};

#endif // GAMETILEDSET_H
