#ifndef TANK_H
#define TANK_H

#include "vehicle/vehicle.h"
#include <QPropertyAnimation>

#define YELLOW_TANK          ":/tank/image/yellow_tank.png"
#define RED_TANK             ":/tank/image/red_tank.png"
#define GREEN_TANK           ":/tank/image/green_tank.png"
#define BLUE_TANK            ":/tank/image/blue_tank.png"
#define GREY_TANK            ":/tank/image/grey_tank.png"
#define EXPLOSION            ":/tank/image/explosion.png"

#define SOUND_FIRE          ":/sounds/sounds/TankFire01.wav"
#define SOUND_EXPLOSION     ":/sounds/sounds/Explosion01.wav"

class GameMap;
class Sound;

class Tank : public Vehicle
{
    Q_OBJECT
    Q_PROPERTY(int firevalue WRITE setFireValue NOTIFY sigFireValue)
    Q_PROPERTY(int lifevalue WRITE setLifeValue NOTIFY sigLifeValue)
public:
    enum COLOR_ID {
        YELLOW, RED, GREEN, BLUE, GREY
    };

    explicit Tank(GameMap *map, int ColorID=YELLOW);
    virtual ~Tank();
    void setFireValue(int value);
    void setLifeValue(int value);
    int FireValue();
    int LifeValue();
    void DecLife(Tank *who_fire);
    void DeathMe(Tank *who_fire);
    bool IsServer();
    void Died();

    void IncShot();
    void IncHit();
    void IncDeath();
    qint16 getShot();
    qint16 getHit();
    qint8 getDeath();
    void setShot(qint16 value);
    void setHit(qint16 value);
    void setDeath(qint8 value);
    Tank *MyKiller();
signals:
    void sigFireValue(int value);
    void sigLifeValue(int value);
    void ChangeStatus(bool fire);
public slots:
    void Fire();
private:
    bool is_server;
    int fire_value;
    qint8 life_value;
    QPropertyAnimation *animation_firebar;
    qint16 total_shots;
    qint16 total_hits;
    qint8 total_deaths;
    Sound *sound_fire;
    Sound *sound_explosion;
    Tank *my_killer;
};

#endif // TANK_H
