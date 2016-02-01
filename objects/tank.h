#ifndef TANK_H
#define TANK_H

#include "vehicle/vehicle.h"
#include <QPropertyAnimation>

#define YELLOW_TANK          ":/tank/image/yellow_tank.png"
#define RED_TANK             ":/tank/image/red_tank.png"
#define GREEN_TANK           ":/tank/image/green_tank.png"
#define BLUE_TANK            ":/tank/image/blue_tank.png"
#define GREY_TANK            ":/tank/image/grey_tank.png"

class GameMap;

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
    void DecLife();
    bool IsServer();
signals:
    void sigFireValue(int value);
    void sigLifeValue(int value);
public slots:
    void Fire();
private:
    bool is_server;
    int fire_value;
    int life_value;
    QPropertyAnimation *animation_firebar;
};

#endif // TANK_H
