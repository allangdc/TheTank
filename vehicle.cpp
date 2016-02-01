#include "vehicle.h"

#include <QDebug>
#include <QtMath>
#include <QGraphicsItemAnimation>
#include <QPropertyAnimation>
#include <QTimeLine>
#include <QTime>

#include "game_camera.h"
#include "game_map.h"
#include "game_tile_colision.h"
#include "game_tile.h"

Vehicle::Vehicle(GameMap *map)
    : QObject(),
      QGraphicsPixmapItem(),
      code(VEHICLE_CODE),
      action(STOP),
      panimation(NULL),
      animation(NULL),
      time_animation(NULL)
{
    this->map = map;

    QTime now = QTime::currentTime();
    while(now == QTime::currentTime());
    qsrand(now.msec());

    id = qrand();

    QPixmap pmap = QPixmap(":/buttons/image/tank_yellow.png");
    setPixmap(pmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    time_animation = new QTimeLine(1000);
    panimation = new QPropertyAnimation(this, "rotation");
    animation = new QGraphicsItemAnimation();
    animation->setItem(this);

    LoadConnections();

    setVelocity(100);
}

Vehicle::~Vehicle()
{
    code = 0;
    if(panimation) {
        delete panimation;
    }
    if(time_animation) {
        delete time_animation;
    }
    if(animation) {
        delete animation;
    }
}

void Vehicle::Move(int action)
{
    if(action >= 0)
        this->action = action;
    switch (this->action) {
    case MOVE_UP:
        MoveUp();
        break;
    case ROTATE_LEFT:
        RotateLeft();
        break;
    case ROTATE_RIGHT:
        RotateRight();
        break;
    case STOP:
    default:
        StopMove();
        break;
    }
}

qreal Vehicle::Velocity()
{
    return velocity;
}

void Vehicle::setVelocity(qreal velocity)
{
    this->velocity = velocity;
}

int Vehicle::CodeObject()
{
    return code;
}

void Vehicle::setRandPos()
{
    qreal x, y;
    qreal w = map->sceneRect().width();
    qreal h = map->sceneRect().height();
    do {
        x = (double) qrand()/(double) RAND_MAX * (w-100) + 50;
        y = (double) qrand()/(double) RAND_MAX * (h-100) + 50;
        setPos(x, y);
    } while(HasCollision());
}

void Vehicle::setRandRotation()
{
    qreal angle;
    do {
        angle = (double) qrand()/(double) RAND_MAX * 360;
        setRotation(angle);
    } while(HasCollision());
}

int Vehicle::ID()
{
    return id;
}

void Vehicle::FinishTimeAnimation()
{
    Move();
}

void Vehicle::MoveTimeAnimation()
{
    GameCamera *view = (GameCamera *) map->views().at(0);
    view->setCentralizeObject();

    Reajusted();
}

void Vehicle::MoveVehicle(int action)
{
    Move(action);
}

bool Vehicle::ReajustCollision(QGraphicsItem *item, int step)
{
    setPos(x(), y()+step);
    if(collidesWithItem(item)) {
        setPos(x(), y()-step*2);
        if(collidesWithItem(item)) {
            setPos(x(), y()+step);
        } else {
            return true;
        }
    } else {
        return true;
    }

    setPos(x()+step, y());
    if(collidesWithItem(item)) {
        setPos(x()-step*2, y());
        if(collidesWithItem(item)) {
            setPos(x()+step, y());
        } else {
            return true;
        }
    } else {
        return true;
    }

    setPos(x()+step, y()+step);
    if(collidesWithItem(item)) {
        setPos(x()-step*2, y()-step*2);
        if(collidesWithItem(item)) {
            setPos(x()+step, y()+step);
        } else {
            return true;
        }
    } else {
        return true;
    }

    setPos(x()-step, y()+step);
    if(collidesWithItem(item)) {
        setPos(x()+step*2, y()-step*2);
        if(collidesWithItem(item)) {
            setPos(x()-step, y()+step);
        } else {
            return true;
        }
    } else {
        return true;
    }

    return false;
}

bool Vehicle::HasCollision()
{
    QList<QGraphicsItem *> colliding = this->collidingItems();
    if(colliding.size()>0) {
        QList<QGraphicsItem *>::iterator it;
        for(it = colliding.begin(); it != colliding.end(); it++) {
            GameTileColision *p = reinterpret_cast<GameTileColision *>(*it);
            if(p->CodeObject() == COLLISION_CODE) {
                return true;
            }
        }
    }
    return false;
}

bool Vehicle::Reajusted()
{
    bool ret = false;
    QList<QGraphicsItem *> colliding = this->collidingItems();
    if(colliding.size()>0) {
        QList<QGraphicsItem *>::iterator it;
        for(it = colliding.begin(); it != colliding.end(); it++) {
            GameTileColision *p = (GameTileColision *) (*it);
            if(p != NULL && p->CodeObject() == COLLISION_CODE) {
                UnloadConnections();
                time_animation->stop();
                for(int i=1; i<20; i++) {
                    if(ReajustCollision(p, i)) {
                        ret = true;
                        break;
                    }
                }
                LoadConnections();
                Move();
            }
        }
    }
    return ret;
}

GameMap *Vehicle::Map()
{
    return map;
}

void Vehicle::LoadConnections()
{
    connect(panimation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(panimation, SIGNAL(valueChanged(QVariant)), this, SLOT(MoveTimeAnimation()));
    connect(time_animation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(time_animation, SIGNAL(valueChanged(qreal)), this, SLOT(MoveTimeAnimation()));
}

void Vehicle::UnloadConnections()
{
    disconnect(panimation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    disconnect(panimation, SIGNAL(valueChanged(QVariant)), this, SLOT(MoveTimeAnimation()));
    disconnect(time_animation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    disconnect(time_animation, SIGNAL(valueChanged(qreal)), this, SLOT(MoveTimeAnimation()));
}

void Vehicle::StopMove()
{
    if(time_animation) {
        time_animation->stop();
        animation->reset();
    }
    if(panimation) {
        panimation->stop();
    }
}

void Vehicle::MoveUp()
{
    panimation->stop();
    animation->reset();
    time_animation->stop();
    time_animation->setDuration(5000);
    time_animation->setFrameRange(0, 120);
    animation->setTimeLine(time_animation);
    animation->setPosAt(0, pos());
    animation->setPosAt(1, NextPosition());
    time_animation->setUpdateInterval(20);
    time_animation->setEasingCurve(QEasingCurve::Linear);
    time_animation->start();
}

void Vehicle::RotateLeft()
{
    time_animation->stop();
    panimation->stop();
    panimation->setDuration(2000);
    panimation->setStartValue(rotation());
    panimation->setEndValue(rotation() - 360.0);
    panimation->start();
}

void Vehicle::RotateRight()
{
    time_animation->stop();
    panimation->stop();
    panimation->setDuration(2000);
    panimation->setStartValue(rotation());
    panimation->setEndValue(rotation() + 360.0);
    panimation->start();
}

QPointF Vehicle::NextPosition()
{
    qreal d = Velocity() * 5;
    QPointF pt;
    pt.setX( pos().x() + d * qSin(qDegreesToRadians(rotation())));
    pt.setY( pos().y() - d * qCos(qDegreesToRadians(rotation())));
    return pt;
}
