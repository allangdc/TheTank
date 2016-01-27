#include "game_map.h"

GameMap::GameMap(QObject *parent) : QGraphicsScene(parent)
{

}

void GameMap::setDimension(int x, int y)
{
    map_id.resize(y);
    QVector< QVector<int> >::iterator it;
    for(it = map_id.begin(); it != map_id.end(); it++)
    {
        it->resize(x);
    }
}

QSize GameMap::Dimension()
{
    QSize sz;
    sz.setHeight(map_id.size());
    sz.setWidth(map_id.at(0).size());
    return sz;
}

void GameMap::setMatrixValue(int x, int y, int value)
{

}

int GameMap::MatrixValue(int x, int y)
{

}

