#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QStack>

#include "game_map.h"

class Vehicle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
public:
    enum EAction {
        STOP = 0, MOVE_UP, ROTATE_LEFT, ROTATE_RIGHT, MOVE_LEFT, MOVE_RIGHT
    };
    explicit Vehicle(GameMap *map);
    virtual ~Vehicle();
    void Move(int action = -1);
public slots:
    void FinishTimeAnimation();
    void MoveTimeAnimation();

    void MoveVehicle(int action);
signals:
    //void ImMoving();
private:
    void StopMove();
    void MoveUp();
    void RotateLeft();
    void RotateRight();
    QPointF NextPosition();
    int action;
    GameMap *map;
    QGraphicsItemAnimation *animation;
    QPropertyAnimation *panimation;
    QTimeLine *time_animation;
    QPointF last_pos;
    qreal last_angle;
    QStack< QPair<QPointF, qreal> > position;
};


#endif // VEHICLE_H
