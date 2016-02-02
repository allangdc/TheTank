#include "bomb.h"

#include "map/game_map.h"
#include "map/game_tile_colision.h"
#include "objects/tank.h"

Bomb::Bomb(GameMap *map, Tank *vehicle)
    : Vehicle(map),
      vehicle(vehicle)
{
    QPixmap pmap = QPixmap(":/tank/image/ball01.png");
    setPixmap(pmap.scaled(10, 10, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    setVelocity(300);
}

void Bomb::Fire()
{
    MoveVehicle(Vehicle::MOVE_UP);
}

bool Bomb::Reajusted()
{
    bool ret = false;
    QList<QGraphicsItem *> colliding = this->collidingItems();
    QList<QGraphicsItem *>::const_iterator it;
    for(it = colliding.begin(); it != colliding.end(); it++) {
        Tank *v = (Tank *) (*it);
        GameTileColision *p = (GameTileColision *) (*it);
        if(v != NULL && v->CodeObject() == VEHICLE_CODE) {
            if(v->ID() != vehicle->ID()) {
                v->DecLife(vehicle);
                deleteLater();
            }
        } else if(p != NULL && p->CodeObject() == COLLISION_CODE) {
            deleteLater();
        }
    }
    return ret;
}
