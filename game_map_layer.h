#ifndef GAMEMAPLAYER_H
#define GAMEMAPLAYER_H

#include <QObject>
#include <QPair>
#include <QVector>
#include <QString>

class GameMap;
class GameTile;

class GameMapLayer : public QObject
{
    Q_OBJECT
public:
    explicit GameMapLayer(GameMap *map);
    void setName(QString name);
    void setEncoding(QString encoding);
    void setDimension(int x, int y);
    void setMatrixValue(int value, int x, int y);
    void setValue(int value, int item);
    void setMatrixTile(GameTile *tile, int x, int y);
    void setTile(GameTile *tile, int item);
    QPair<int, GameTile*> Matrix(int x, int y);
    QPair<int, GameTile*> Item(int item);
    QString Name();
    QString Encoding();
    QSize Dimension();
private:
    QVector< QVector< QPair<int, GameTile*> > > map_id;
    QString name;
    QString encoding;
    GameMap *map;
};

#endif // GAMEMAPLAYER_H
