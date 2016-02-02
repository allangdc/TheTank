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
//        vehicle_status->code = CODE_VEHICLE;
//        vehicle_status->pos = v->pos();
//        vehicle_status->angle = v->rotation();
//        vehicle_status->id = v->ID();
//        vehicle_status->fire = 0;
//        vehicle_status->action = v->Action();
//        vehicle_status->life = (unsigned char) (v->LifeValue()/10);
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
                v->setLifeValue(vstatus->life * 10);
            } else {
                v = engine->CreateTank(true);
                v->setLifeValue(100);
            }
            v->setPos(vstatus->pos);
            v->setRotation(vstatus->angle);
            v->setID(vstatus->id);
            v->MoveVehicle(vstatus->action);
        }
    } else if(map->total == vehicles->size()) {
        for(int i=0; i<map->total; i++) {
            struct VehicleStatus *vstatus = &(map->status[i]);
            Tank *v = vehicles->at(i);
            v->setPos(vstatus->pos);
            v->setRotation(vstatus->angle);
            v->setID(vstatus->id);
            v->MoveVehicle(vstatus->action);
            v->setLifeValue(vstatus->life * 10);
        }
    } else {
        for(int i=0; i<map->total; i++) {
            struct VehicleStatus *vstatus = &(map->status[i]);
            Tank *v;
            if(i != map->total-1)
                v = vehicles->at(i);
            else
                v = engine->CreateTank();
            v->setPos(vstatus->pos);
            v->setRotation(vstatus->angle);
            v->setID(vstatus->id);
            v->MoveVehicle(vstatus->action);
            v->setLifeValue(vstatus->life * 10);
        }
    }
}

void GameProtocol::SendTankStatus(bool fire)
{
    struct VehicleStatus v;
    Tank *t = engine->MainTank();
    v.code = CODE_VEHICLE;
    v.pos = t->pos();
    v.angle = t->rotation();
    v.id = t->ID();
    v.fire = fire?1:0;
    v.action = t->Action();
    v.life = (unsigned char) (t->LifeValue() / 10);
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
                t->setPos(v->pos);
                t->setRotation(v->angle);
                t->setID(v->id);
                t->MoveVehicle(v->action);
                t->setLifeValue(v->life * 10);
                if(v->fire == 1) {
                    t->Fire();
                }
            } else {
                t->setLifeValue(v->life * 10);
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
    v.life = (unsigned char) (tank->LifeValue()/10);
    v.total_shots = tank->getShot();
    v.total_hits = tank->getHit();
    v.total_deaths = tank->getDeath();
    return v;
}

unsigned char GameProtocol::GetCode(QByteArray array)
{
    unsigned char code = (unsigned char) array.at(0);
    return code;
}




