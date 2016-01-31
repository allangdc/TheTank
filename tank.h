#ifndef TANK_H
#define TANK_H

#include "vehicle.h"

class GameMap;

class Tank : public Vehicle
{
    Q_OBJECT
public:
    explicit Tank(GameMap *map);
public slots:
    void Fire();
};

#endif // TANK_H
