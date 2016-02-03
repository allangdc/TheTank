#include "objects/tank.h"

#include <QPropertyAnimation>
#include <QPixmap>
#include <QtMath>

#include "map/game_map.h"
#include "bomb.h"
#include "sound.h"

Tank::Tank(GameMap *map, int ColorID)
    : Vehicle(map),
      is_server(true),
      fire_value(100),
      life_value(100),
      total_deaths(0),
      total_shots(0),
      total_hits(0),
      my_killer(NULL)
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

    InitSound();

    sound_fire = new Sound(SOUND_FIRE);
    sound_explosion = new Sound(SOUND_EXPLOSION);
}

Tank::~Tank()
{
    delete animation_firebar;
    delete sound_fire;
    delete sound_explosion;
}

void Tank::Fire()
{
    if(!IsAlive())
        return;

    emit ChangeStatus(true);
    if(fire_value == 100) {
        IncShot();
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

        sound_fire->Play(false);
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

void Tank::DecLife(Tank *who_fire)
{
    who_fire->IncHit();
    if(IsServer()) {
        if(LifeValue()>=10) {
            setLifeValue(LifeValue()-10);
            emit ChangeStatus(false);
            if(LifeValue() <= 0) {
                DeathMe(who_fire);
            }
        }
    }
}

void Tank::DeathMe(Tank *who_fire)
{
    setLifeValue(0);
    if(who_fire)
        who_fire->IncDeath();
    my_killer = who_fire;
    Died();
}

bool Tank::IsServer()
{
    return is_server;
}

void Tank::Died()
{
    setAlive(false);
    MoveVehicle(Vehicle::STOP);

    QPixmap pmap = QPixmap(EXPLOSION);
    setPixmap(pmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    sound_explosion->Play(false);
}

void Tank::IncShot()
{
    total_shots++;
}

void Tank::IncHit()
{
    total_hits++;
}

void Tank::IncDeath()
{
    total_deaths++;
}

qint16 Tank::getShot()
{
    return total_shots;
}

qint16 Tank::getHit()
{
    return total_hits;
}

qint8 Tank::getDeath()
{
    return total_deaths;
}

void Tank::setShot(qint16 value)
{
    total_shots = value;
}

void Tank::setHit(qint16 value)
{
    total_hits = value;
}

void Tank::setDeath(qint8 value)
{
    total_deaths = value;
}

Tank *Tank::MyKiller()
{
    return my_killer;
}



