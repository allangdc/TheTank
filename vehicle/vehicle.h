#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

#define VEHICLE_CODE        0xC0DE

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
        STOP            = 0b0000,
        MOVE_UP         = 0b0001,
        ROTATE_LEFT     = 0b0110,
        ROTATE_RIGHT    = 0b0100,
        MOVE_LEFT       = 0b0111,
        MOVE_RIGHT      = 0b0101
    };
    explicit Vehicle(GameMap *map);
    virtual ~Vehicle();
    void Move(int action = -1);
    qreal Velocity();
    void setVelocity(qreal velocity);
    int CodeObject();
    void setRandPos();
    void setRandRotation();
    int ID();
public slots:
    void FinishTimeAnimation();
    void MoveTimeAnimation();
    void MoveVehicle(int action);
protected:
    bool HasCollision();
    bool ReajustCollision(QGraphicsItem *item, int step);
    virtual bool Reajusted();
    GameMap *Map();

private:
    void LoadConnections();
    void UnloadConnections();
    void StopMove();
    void MoveUp();
    void RotateLeft();
    void RotateRight();
    QPointF NextPosition();

    int code;
    int id;
    int action;
    GameMap *map;
    QGraphicsItemAnimation *animation;
    QPropertyAnimation *panimation;
    qreal velocity;
    QTimeLine *time_animation;
};


#endif // VEHICLE_H