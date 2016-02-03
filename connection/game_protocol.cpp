#include "game_protocol.h"

#include "objects/tank.h"
#include "connection/game_client.h"
#include "connection/game_server.h"
#include "map/game_map.h"
#include "gameengine.h"

GameProtocol::GameProtocol(GameMap *map,
                           GameEngine *engine,
                           QVector<Tank *> *vehicles,
                           GameServer *server,
                           GameClient *client,
                           QString ip,
                           int port)
    : QObject(),
      game_map(map),
      engine(engine),
      vehicles(vehicles),
      conn_server(server),
      conn_client(client),
      ip(ip),
      port(port)
{
}

void GameProtocol::GenerateMap()
{
    struct MapStatus map;
    map.code = CODE_MAP;
    map.total = vehicles->size();
    for(int i=0; i<map.total; i++) {
        struct VehicleStatus *vehicle_status = &(map.status[i]);
        Tank *v = vehicles->at(i);
        *vehicle_status = Status(v);
    }
    QByteArray array((char *) &map, sizeof(struct MapStatus));
    conn_server->BroadcastMessage(array);
}

void GameProtocol::ReceiverMap(QByteArray array)
{
    struct MapStatus *map;
    map = (struct MapStatus *) array.data();
    if(engine->MainTank() == NULL) {
        vehicles->clear();
        for(int i=0; i<map->total; i++) {
            struct VehicleStatus *vstatus = &(map->status[i]);
            Tank *v;
            if(i != map->total-1) {
                v = engine->CreateTank();
                Status(v, *vstatus);
                v->setLifeValue(vstatus->life);
            } else {
                v = engine->CreateTank(true);
                Status(v, *vstatus);
                v->setLifeValue(100);
            }
        }
    } else if(map->total == vehicles->size()) {
        for(int i=0; i<map->total; i++) {
            struct VehicleStatus *vstatus = &(map->status[i]);
            Tank *v = vehicles->at(i);
            Status(v, *vstatus);
        }
    } else {
        for(int i=0; i<map->total; i++) {
            struct VehicleStatus *vstatus = &(map->status[i]);
            Tank *v;
            if(i != map->total-1)
                v = vehicles->at(i);
            else
                v = engine->CreateTank();
            Status(v, *vstatus);
        }
    }
}

void GameProtocol::SendTankDiedStatus(int tank_id) {
    struct VehicleStatus v;
    Tank *t = engine->MainTank();
    v = Status(t);
    v.died = 1;
    v.id_who_died_me = tank_id;
    QByteArray array((char *) &v, sizeof(struct Vehicle));
    if(conn_client)
        conn_client->SendMessage(array);
    else if(conn_server)
        conn_server->BroadcastMessage(array);
}

void GameProtocol::SendTankStatus(bool fire)
{
    struct VehicleStatus v;
    Tank *t = engine->MainTank();
    v = Status(t);
    v.fire = fire?1:0;
    QByteArray array((char *) &v, sizeof(struct Vehicle));
    if(conn_client)
        conn_client->SendMessage(array);
    else if(conn_server)
        conn_server->BroadcastMessage(array);
}

void GameProtocol::ReceiverTankStatus(QByteArray array)
{
    struct VehicleStatus *v;
    v = (struct VehicleStatus *) array.data();
    Tank *t = NULL;
    for(int i=0; i<vehicles->size(); i++)
    {
        t = vehicles->at(i);
        if(v->id == t->ID())
            break;
    }

    if(t) {
        Tank *mytank = engine->MainTank();
        if(mytank) {
            if(mytank->ID() != t->ID()) {
                Status(t, *v);
            } else {
                //t->setLifeValue(v->life);
            }
        }
    }
}

void GameProtocol::SendMovement()
{
    SendTankStatus();
}

void GameProtocol::SendMovement(bool fire)
{
    SendTankStatus(fire);
}

VehicleStatus GameProtocol::Status(Tank *tank)
{
    VehicleStatus v;
    v.code = CODE_VEHICLE;
    v.pos = tank->pos();
    v.angle = tank->rotation();
    v.id = tank->ID();
    v.fire = 0;
    v.action = tank->Action();
    v.life = tank->LifeValue();
    v.total_shots = tank->getShot();
    v.total_hits = tank->getHit();
    v.total_deaths = tank->getDeath();
    v.died = 0;
    v.id_who_died_me = 0;
    return v;
}

void GameProtocol::Status(Tank *tank, VehicleStatus vehicle)
{
    tank->setPos(vehicle.pos);
    tank->setRotation(vehicle.angle);
    tank->setID(vehicle.id);
    tank->MoveVehicle(vehicle.action);
    tank->setLifeValue(vehicle.life);
    tank->setShot(vehicle.total_shots);
    tank->setHit(vehicle.total_hits);
    tank->setDeath(vehicle.total_deaths);
    if(vehicle.fire)
        tank->Fire();
    if(vehicle.died) {
        tank->DeathMe(engine->TankByID(vehicle.id_who_died_me));
    }
}

unsigned char GameProtocol::GetCode(QByteArray array)
{
    unsigned char code = (unsigned char) array.at(0);
    return code;
}




