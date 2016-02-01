#include "tank.h"

#include <QPropertyAnimation>

#include "game_map.h"
#include "bomb.h"

Tank::Tank(GameMap *map)
    : Vehicle(map),
      fire_value(100),
      life_value(100)
{
    setVelocity(100);
    animation_firebar = new QPropertyAnimation(this, "firevalue");
    animation_firebar->setDuration(5000);
    animation_firebar->setStartValue(0);
    animation_firebar->setEndValue(100);
    animation_firebar->setEasingCurve(QEasingCurve::Linear);
}

Tank::~Tank()
{
    delete animation_firebar;
}

void Tank::Fire()
{
    if(fire_value == 100) {
        Bomb *bomb = new Bomb(Map(), this);

        QPointF pt;     //position of the bomb
        QPointF ori;    //center of the rotation
        pt.setY(this->y() - bomb->pixmap().height()/2);
        pt.setX(this->x() + this->pixmap().width()/2 - bomb->pixmap().width()/2);
        ori.setX(bomb->pixmap().width()/2);
        ori.setY(this->transformOriginPoint().y() + bomb->pixmap().height()/2);
        bomb->setPos(pt);
        bomb->setTransformOriginPoint(ori);
        bomb->setRotation(this->rotation());

        Map()->addItem(bomb);
        bomb->Fire();
    }

    animation_firebar->stop();
    animation_firebar->start();
}

void Tank::setFireValue(int value)
{
    fire_value = value;
    emit sigFireValue(value);
}

void Tank::setLifeValue(int value)
{
    life_value = value;
}
