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
    unsigned char life;
    qint16 total_shots;
    qint16 total_hits;
    qint8 total_deaths;
    unsigned char fire      : 1;
    unsigned char action    : 3;
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
        CODE_MAP, CODE_VEHICLE
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
    void ReceiverTankStatus(QByteArray array);
public slots:
    void SendMovement();
    void SendMovement(bool fire);
private:
    VehicleStatus Status(Tank *tank);
    QVector<Tank *> *vehicles;
    GameMap *game_map;
    GameEngine *engine;
    GameServer *conn_server;
    GameClient *conn_client;
    int port;
    QString ip;
};

#endif // GAME_PROTOCOL_H
