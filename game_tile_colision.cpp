#include "game_tile_colision.h"

#include <QStringList>
#include <QPolygonF>
#include <QDebug>

GameTileColision::GameTileColision(QString list_points, GameTile *tile)
    : QGraphicsPolygonItem(),
      code(COLLISION_CODE)
{
    this->tile = tile;
    QStringList list = list_points.split(" ");
    QStringList::iterator it;
    QPolygonF pol;
    for(it = list.begin(); it != list.end(); it++) {
        QStringList p = it->split(",");
        QPointF pt(p.at(0).toFloat(), p.at(1).toFloat());
        pol.push_back(pt);
    }
    this->setPolygon(pol);
}

GameTileColision::GameTileColision(const GameTileColision *c)
    :QGraphicsPolygonItem(c->polygon()),
      code(COLLISION_CODE)
{
    this->tile = c->tile;
    this->draw_order = c->draw_order;
    this->id = c->id;
    this->point = c->point;
    this->setPolygon(c->polygon());
}

GameTileColision::~GameTileColision()
{
    code = 0;
}

void GameTileColision::setDrawOrder(QString value)
{
    draw_order = value;
}

void GameTileColision::setID(int value)
{
    id = value;
}

void GameTileColision::setPoint(qreal x, qreal y)
{
    point.setX(x);
    point.setY(y);
    QPolygonF::iterator it;
    QPolygonF pol = this->polygon();
    for(it = pol.begin(); it != pol.end(); it++) {
        it->setX(it->x() + x);
        it->setY(it->y() + y);
    }
    this->setPolygon(pol);
}

QString GameTileColision::DrawOrder()
{
    return draw_order;
}

int GameTileColision::ID()
{
    return id;
}

QPointF GameTileColision::Point()
{
    return point;
}

GameTile *GameTileColision::Tile()
{
    return tile;
}

QRectF GameTileColision::Rect()
{
    QPolygonF::iterator it;
    QPolygonF pol = this->polygon();
    QPointF max(-999,-999), min(999,999);
    for(it = pol.begin(); it != pol.end(); it++) {
        if(it->x() > max.x())
            max.setX(it->x());
        if(it->x() < min.x())
            min.setX(it->x());

        if(it->y() > max.y())
            max.setY(it->y());
        if(it->y() < min.y())
            min.setY(it->y());
    }
    return QRectF(min, max);
}
