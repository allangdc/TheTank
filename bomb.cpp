#include "bomb.h"

#include "game_map.h"
#include "game_tile_colision.h"

Bomb::Bomb(GameMap *map, Vehicle *vehicle)
    : Vehicle(map),
      vehicle(vehicle)
{
    QPixmap pmap = QPixmap(":/tank/image/ball01.png");
    setPixmap(pmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    setVelocity(800);
}

void Bomb::Fire()
{
    MoveVehicle(Vehicle::MOVE_UP);
}

bool Bomb::Reajusted()
{
    bool ret = false;
    QList<QGraphicsItem *> colliding = this->collidingItems();
    QList<QGraphicsItem *>::iterator it;
    for(it = colliding.begin(); it != colliding.end(); it++) {
        GameTileColision *p = reinterpret_cast<GameTileColision *>(*it);
        if(p->CodeObject() == COLLISION_CODE) {
            deleteLater();
            //@TODO: Implementar a colisão com um veículo
        }
    }
    return ret;
}
