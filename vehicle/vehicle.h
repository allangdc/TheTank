#ifndef VEHICLE_H
#define VEHICLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

#define VEHICLE_CODE        0xC0DE
#define EXPLOSION_CODE      0xA1A1

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
        STOP            = 0b000,
        MOVE_UP         = 0b001,
        ROTATE_LEFT     = 0b110,
        ROTATE_RIGHT    = 0b100,
        MOVE_LEFT       = 0b111,
        MOVE_RIGHT      = 0b101
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
    void setID(int id);
    int Action();
signals:
    void ChangeStatus();
public slots:
    void FinishTimeAnimation();
    void MoveTimeAnimation();
    void MoveVehicle(int action);
    void TimeOut();
protected:
    bool HasCollision();
    bool ReajustCollision(QGraphicsItem *item, int step);
    virtual bool Reajusted();
    GameMap *Map();
    void setAlive(bool value);
    bool IsAlive();
private:
    void LoadConnections();
    void UnloadConnections();
    void StopMove();
    void MoveUp();
    void RotateLeft();
    void RotateRight();
    QPointF NextPosition();
    int id;
    int code;
    int action;
    GameMap *map;
    QGraphicsItemAnimation *animation;
    QPropertyAnimation *panimation;
    qreal velocity;
    QTimeLine *time_animation;
    QTimer *timer;
    bool is_alive;
};


#endif // VEHICLE_H
