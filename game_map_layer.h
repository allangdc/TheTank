#ifndef GAMEMAPLAYER_H
#define GAMEMAPLAYER_H

#include <QObject>
#include <QPair>
#include <QVector>
#include <QString>

#include "game_tile.h"

class GameMap;

class GameMapLayer : public QObject
{
    Q_OBJECT
public:
    explicit GameMapLayer(GameMap *map);
    void setName(QString name);
    void setEncoding(QString encoding);
    void setDimension(int x, int y);
    void setMatrixValue(int value, int x, int y);
    void setMatrixTile(GameTile *tile, int x, int y);
    QPair<int, GameTile*> Matrix(int x, int y);
    QString Name();
    QString Encoding();
    QSize Dimension();
private:
    QVector< QVector< QPair<int, GameTile*> > > map_id;
    QString name;
    QString encoding;
};

#endif // GAMEMAPLAYER_H
