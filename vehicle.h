#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

#define VEHICLE_CODE        12345

class GameMap;
class QGraphicsItemAnimation;
class QPropertyAnimation;
class QTimeLine;

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
    qreal Velocity();
    void setVelocity(qreal velocity);
    int CodeObject();
public slots:
    void FinishTimeAnimation();
    void MoveTimeAnimation();
    void MoveVehicle(int action);
protected:
    bool ReajustCollision(QGraphicsItem *item, int step);
    virtual bool Reajusted();
    GameMap *Map();

    QTimeLine *time_animation;
private:
    void StopMove();
    void MoveUp();
    void RotateLeft();
    void RotateRight();
    QPointF NextPosition();

    int code;
    int action;
    GameMap *map;
    QGraphicsItemAnimation *animation;
    QPropertyAnimation *panimation;
    qreal velocity;
};


#endif // VEHICLE_H
