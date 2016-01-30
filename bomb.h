#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPointF>

class Vehicle;
class GameMap;
class QGraphicsItemAnimation;
class QTimeLine;

class Bomb : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Bomb(GameMap *map, Vehicle *vehicle);
    void Fire();
private:
    void MoveUp();
    QPointF NextPosition();
    Vehicle *vehicle;
    GameMap *map;
    QGraphicsItemAnimation *animation;
    QTimeLine *time_animation;
};

#endif // BOMB_H
