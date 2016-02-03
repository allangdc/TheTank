#ifndef BOMB_H
#define BOMB_H

#include "vehicle/vehicle.h"

class Tank;
class Sound;

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
    Sound *sound_fire;
    Sound *sound_explosion;
};

#endif // BOMB_H
