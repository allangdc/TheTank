#include "vehicle.h"

#include <QTimeLine>
#include <QDebug>
#include <QtMath>
#include <QGraphicsView>

Vehicle::Vehicle(GameMap *map)
    : QObject(map),
      QGraphicsPixmapItem(),
      action(STOP),
      panimation(NULL),
      animation(NULL),
      time_animation(NULL)
{
    this->map = map;

    QPixmap pmap = QPixmap(":/buttons/image/tank_yellow.png");
    setPixmap(pmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    animation = new QGraphicsItemAnimation(this);
    animation->setItem(this);

    this->setPos(200,200);
    this->setRotation(90+45);
}

Vehicle::~Vehicle()
{
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

void Vehicle::FinishTimeAnimation()
{
    Move();
}

void Vehicle::MoveTimeAnimation()
{
    QGraphicsView *view = map->views().at(0);
    view->centerOn(this);
}

void Vehicle::MoveVehicle(int action)
{
    Move(action);
}

void Vehicle::StopMove()
{
    if(time_animation) {
        time_animation->stop();
        delete time_animation;
        time_animation = NULL;
    }
    if(panimation) {
        panimation->stop();
        delete panimation;
        panimation = NULL;
    }
}

void Vehicle::MoveUp()
{
    if(panimation) {
        delete panimation;
        panimation = NULL;
    }
    if(time_animation) {
        delete time_animation;
        time_animation = NULL;
    }
    time_animation = new QTimeLine(1000, this);
    connect(time_animation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(time_animation, SIGNAL(valueChanged(qreal)), this, SLOT(MoveTimeAnimation()));
    time_animation->stop();
    time_animation->setDuration(1000);
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
    if(time_animation) {
        delete time_animation;
        time_animation = NULL;
    }
    if(panimation) {
        delete panimation;
        panimation = NULL;
    }
    panimation = new QPropertyAnimation(this, "rotation", this);
    connect(panimation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(panimation, SIGNAL(valueChanged(QVariant)), this, SLOT(MoveTimeAnimation()));
    panimation->setDuration(2000);
    panimation->setStartValue(rotation());
    panimation->setEndValue(rotation() - 360.0);
    panimation->start();
}

void Vehicle::RotateRight()
{
    if(time_animation) {
        delete time_animation;
        time_animation = NULL;
    }
    if(panimation) {
        delete panimation;
        panimation = NULL;
    }
    panimation = new QPropertyAnimation(this, "rotation", this);
    connect(panimation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(panimation, SIGNAL(valueChanged(QVariant)), this, SLOT(MoveTimeAnimation()));
    panimation->setDuration(2000);
    panimation->setStartValue(rotation());
    panimation->setEndValue(rotation() + 360.0);
    panimation->start();
}



QPointF Vehicle::NextPosition()
{
    qreal d = 100;
    QPointF pt;
    qDebug() << "Rotation: " << rotation();
    pt.setX( pos().x() + d * qSin(qDegreesToRadians(rotation())));
    pt.setY( pos().y() - d * qCos(qDegreesToRadians(rotation())));
    return pt;
}