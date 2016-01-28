#include "game_map_layer.h"

#include "game_map.h"

GameMapLayer::GameMapLayer(GameMap *map)
    : QObject()
{

}

void GameMapLayer::setName(QString name)
{
    this->name = name;
}

void GameMapLayer::setEncoding(QString encoding)
{
    this->encoding = encoding;
}

void GameMapLayer::setDimension(int x, int y)
{
    map_id.resize(y);
    QVector< QVector< QPair<int, GameTile*> > >::iterator it_y;
    for(it_y = map_id.begin(); it_y != map_id.end(); it_y++)
    {
        it_y->resize(x);
    }
}

void GameMapLayer::setMatrixValue(int value, int x, int y)
{
    QVector< QPair<int, GameTile*> > *vy = &(map_id[y]);
    (*vy)[x].first = value;
}

void GameMapLayer::setMatrixTile(GameTile *tile, int x, int y)
{
    QVector< QPair<int, GameTile*> > *vy = &(map_id[y]);
    (*vy)[x].second = tile;
}

QPair<int, GameTile *> GameMapLayer::Matrix(int x, int y)
{
    QVector< QPair<int, GameTile*> > *vy = &(map_id[y]);
    return (*vy).at(x);
}

QString GameMapLayer::Name()
{
    return name;
}

QString GameMapLayer::Encoding()
{
    return encoding;
}

QSize GameMapLayer::Dimension()
{
    QSize sz;
    sz.setHeight(map_id.size());
    sz.setWidth(map_id.at(0).size());
    return sz;
}
