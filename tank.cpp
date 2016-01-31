#include "tank.h"

#include "game_map.h"
#include "bomb.h"

Tank::Tank(GameMap *map)
    : Vehicle(map)
{
    setVelocity(400);
}

void Tank::Fire()
{
    Bomb *bomb = new Bomb(Map(), this);
    bomb->setPos(pos());
    bomb->setRotation(rotation());
    Map()->addItem(bomb);
    bomb->Fire();
}
