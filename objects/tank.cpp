#include "objects/tank.h"

#include <QPropertyAnimation>
#include <QPixmap>
#include <QtMath>

#include "map/game_map.h"
#include "bomb.h"

Tank::Tank(GameMap *map, int ColorID)
    : Vehicle(map),
      is_server(true),
      fire_value(100),
      life_value(100)
{
    QPixmap pmap;
    switch (ColorID) {
    case YELLOW:
        pmap = QPixmap(YELLOW_TANK);
        break;
    case RED:
        pmap = QPixmap(RED_TANK);
        break;
    case BLUE:
        pmap = QPixmap(BLUE_TANK);
        break;
    case GREEN:
        pmap = QPixmap(GREEN_TANK);
        break;
    case GREY:
    default:
        pmap = QPixmap(GREY_TANK);
        break;
    }
    //QPixmap pmap = QPixmap(YELLOW_TANK);
    QTransform transform;
    QTransform trans = transform.rotate(90);
    pmap = pmap.transformed(trans);
    setPixmap(pmap.scaled(30, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

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
    emit sigLifeValue(value);
}

int Tank::FireValue()
{
    return fire_value;
}

int Tank::LifeValue()
{
    return life_value;
}

void Tank::DecLife()
{
    if(IsServer()) {
        if(LifeValue()>=10) {
            setLifeValue(LifeValue()-50);
            if(LifeValue() <= 0)
                deleteLater();
        }
    }
}

bool Tank::IsServer()
{
    return is_server;
}
