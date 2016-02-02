#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVector>

class QWidget;
class GameMap;
class GameCamera;
class Vehicle;
class Tank;
class GameServer;
class GameClient;
class GameProtocol;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent);
    void setCamera(GameCamera *camera);
    GameCamera *Camera();
    void InitScene(QString tmxfile);
    Tank *CreateTank(bool main_tank=false);
    void setMainTank(Tank *tank);
    Tank *MainTank();
    void setConnection(bool is_server, QString ip, int port);
    bool IsServer();
    QString IpPort();
private:
    Tank *my_tank;
    GameProtocol *protocol;
    GameCamera *camera;
    GameMap *scene;
    QVector<Tank *> vehicles;
    GameServer *conn_server;
    GameClient *conn_client;
    QString ip;
    int port;
public slots:
    void ServerInitConnection(int id);
    void ServerReceiveMSG(int id, QByteArray array);
    void ClientReceiveMSG(QByteArray array);
};

#endif // GAMEENGINE_H
