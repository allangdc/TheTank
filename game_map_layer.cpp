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

void GameMapLayer::setValue(int value, int item)
{
    int x, y;
    y = item / Dimension().width();
    x = y*Dimension().width() + Dimension().height();
    setMatrixValue(value, x, y);
}

void GameMapLayer::setMatrixTile(GameTile *tile, int x, int y)
{
    QVector< QPair<int, GameTile*> > *vy = &(map_id[y]);
    (*vy)[x].second = tile;
}

void GameMapLayer::setTile(GameTile *tile, int item)
{
    int x, y;
    y = item / Dimension().width();
    x = y*Dimension().width() + Dimension().height();
    setMatrixTile(tile, x, y);
}

QPair<int, GameTile *> GameMapLayer::Matrix(int x, int y)
{
    QVector< QPair<int, GameTile*> > *vy = &(map_id[y]);
    return (*vy).at(x);
}

QPair<int, GameTile *> GameMapLayer::Item(int item)
{
    int x, y;
    y = item / Dimension().width();
    x = y*Dimension().width() + Dimension().height();
    return Matrix(x, y);
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
