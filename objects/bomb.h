#ifndef BOMB_H
#define BOMB_H

#include "vehicle/vehicle.h"

class Tank;

class Bomb : public Vehicle
{
    Q_OBJECT
public:
    Bomb(GameMap *map, Tank *vehicle);
    void Fire();
protected:
    virtual bool Reajusted();
private:
    Tank *vehicle;
};

#endif // BOMB_H
