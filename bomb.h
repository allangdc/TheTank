#ifndef BOMB_H
#define BOMB_H

#include "vehicle.h"

class Bomb : public Vehicle
{
    Q_OBJECT
public:
    Bomb(GameMap *map, Vehicle *vehicle);
    void Fire();
protected:
    virtual bool Reajusted();
private:
    Vehicle *vehicle;
};

#endif // BOMB_H
