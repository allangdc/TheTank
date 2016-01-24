#include "game_tile.h"

GameTile::GameTile(Tile tile, QObject *parent)
    : QObject(parent)
{

}

GameTile::GameTile(const GameTile &tile)
{
    id = tile.id;
    probability = tile.probability;
    durations = tile.durations;
    QVector<QGraphicsPixmapItem *>::const_iterator it;
    for(it = tile.images.begin(); it != tile.images.end(); it++) {
        QGraphicsPixmapItem *graphic = new QGraphicsPixmapItem(*it);
        images.push_back(graphic);
    }
}

GameTile::~GameTile()
{
    QVector<QGraphicsPixmapItem *>::const_iterator it;
    for(it = images.begin(); it != images.end(); it++) {
        QGraphicsPixmapItem *graphic = *it;
        delete graphic;
    }
}

void GameTile::setImage(QPixmap *pixmap, QRect region)
{
    images.clear();
    durations.clear();
    QPixmap pxm = pixmap->copy(region);
    QGraphicsPixmapItem *graphic = new QGraphicsPixmapItem(pxm);
    images.push_back(graphic);
    durations.push_back(-1);
}

void GameTile::addImage(QPixmap *pixmap,
                        QRect region,
                        qreal duration)
{
    QPixmap pxm = pixmap->copy(region);
    QGraphicsPixmapItem *graphic = new QGraphicsPixmapItem(pxm);
    images.push_back(graphic);
    durations.push_back(duration);
}

QGraphicsPixmapItem *GameTile::Image(int index)
{
    if (images.size()>0)
        return images.at(index);
    else
        return NULL;
}

