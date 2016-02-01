#ifndef TANK_H
#define TANK_H

#include "vehicle.h"
#include <QPropertyAnimation>

class GameMap;

class Tank : public Vehicle
{
    Q_OBJECT
    Q_PROPERTY(int firevalue WRITE setFireValue NOTIFY sigFireValue)
    Q_PROPERTY(int lifevalue WRITE setLifeValue NOTIFY sigLifeValue)
public:
    explicit Tank(GameMap *map);
    virtual ~Tank();
signals:
    void sigFireValue(int value);
    void sigLifeValue(int value);
public slots:
    void Fire();
private:
    void setFireValue(int value);
    void setLifeValue(int value);
    int fire_value;
    int life_value;
    QPropertyAnimation *animation_firebar;
};

#endif // TANK_H
