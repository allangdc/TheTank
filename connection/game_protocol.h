#ifndef GAME_PROTOCOL_H
#define GAME_PROTOCOL_H

#include <QObject>
#include <QPointF>
#include <QVector>
#include <QByteArray>

struct VehicleStatus {
    unsigned char code;
    QPointF pos;
    qreal angle;
    int id;
    qint8 life;
    qint16 total_shots;
    qint16 total_hits;
    qint8 total_deaths;
    int id_who_died_me;
    unsigned char fire      : 1;
    unsigned char action    : 3;
    unsigned char died      : 1;
};

struct MapStatus {
    unsigned char code;
    unsigned char total;
    struct VehicleStatus status[5];
};

class GameMap;
class GameServer;
class GameClient;
class GameEngine;
class Tank;

class GameProtocol: public QObject
{
    Q_OBJECT
public:
    enum code {
        CODE_MAP, CODE_VEHICLE, CODE_EXIT
    };

    GameProtocol(GameMap *map,
                 GameEngine *engine,
                 QVector<Tank *> *vehicles,
                 GameServer *server,
                 GameClient *client,
                 QString ip,
                 int port);
    unsigned char GetCode(QByteArray array);
    void GenerateMap();
    void ReceiverMap(QByteArray array);
    void SendTankStatus(bool fire=false);
    void SendTankDiedStatus(int tank_id);
    void ReceiverTankStatus(QByteArray array);
public slots:
    void SendMovement();
    void SendMovement(bool fire);
private:
    VehicleStatus Status(Tank *tank);
    void Status(Tank *tank, VehicleStatus vehicle);
    QVector<Tank *> *vehicles;
    GameMap *game_map;
    GameEngine *engine;
    GameServer *conn_server;
    GameClient *conn_client;
    int port;
    QString ip;
};

#endif // GAME_PROTOCOL_H
