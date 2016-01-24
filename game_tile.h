#ifndef GAMETILE_H
#define GAMETILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QString>

#include "tmxfiles.h"

class GameTile : public QObject
{
    Q_OBJECT
public:
    GameTile(Tile tile, QObject *parent = 0);
    GameTile(const GameTile &tile);
    virtual ~GameTile();
    void setImage(QPixmap *pixmap, QRect region);
    void addImage(QPixmap *pixmap, QRect region, qreal duration);
    QGraphicsPixmapItem *Image(int index = 0);
private:
    int id;
    qreal probability;
    QVector<QGraphicsPixmapItem *> images;
    QVector<qreal> durations;
};

#endif // GAMETILE_H
