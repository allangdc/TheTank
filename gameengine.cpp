#include "gameengine.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

#include "mainwindow.h"
#include "map/game_tmx_map.h"
#include "map/game_map.h"
#include "map/game_camera.h"
#include "vehicle/vehicle.h"
#include "objects/tank.h"
#include "connection/game_client.h"
#include "connection/game_server.h"
#include "connection/game_protocol.h"

GameEngine::GameEngine(QWidget *parent)
    : QObject(parent),
      camera(NULL),
      scene(NULL),
      conn_client(NULL),
      conn_server(NULL),
      my_tank(NULL)
{

}

void GameEngine::setCamera(GameCamera *camera)
{
    this->camera = camera;

    camera->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    camera->setCacheMode(QGraphicsView::CacheBackground);
    camera->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

GameCamera *GameEngine::Camera()
{
    return camera;
}

void GameEngine::InitScene(QString tmxfile)
{
    scene = new GameMap();
    GameTMXMap *tmx = new GameTMXMap(scene);
    qDebug() << "RESULT=" << tmx->LoadTMXFile(tmxfile);
    scene->LoadFullMap();

    camera->setScene(scene);
}

Tank *GameEngine::CreateTank(bool main_tank)
{
    static int i=0;
    Tank *v = new Tank(scene, i++);
    scene->addItem(v);
    v->setRandPos();
    v->setRandRotation();
    vehicles.push_back(v);

    if(main_tank) {
        setMainTank(v);
    }

    return v;
}

void GameEngine::setMainTank(Tank *tank)
{
    MainWindow *mainwindow = reinterpret_cast<MainWindow *>(parent());
    camera->setCentralizeObject(tank);
    connect(mainwindow, SIGNAL(MoveTankAction(int)), tank, SLOT(MoveVehicle(int)));
    connect(mainwindow, SIGNAL(TankFire()), tank, SLOT(Fire()));
    connect(tank, SIGNAL(sigFireValue(int)), mainwindow, SLOT(setFireProgress(int)));
    connect(tank, SIGNAL(sigLifeValue(int)), mainwindow, SLOT(setLifeProgress(int)));
    connect(camera, SIGNAL(Click()), tank, SLOT(Fire()));
    camera->setCentralizeObject(tank);
    tank->setFireValue(100);
    tank->setLifeValue(100);
    connect(tank, SIGNAL(ChangeStatus()), protocol, SLOT(SendMovement()));
    connect(tank, SIGNAL(ChangeStatus(bool)), protocol, SLOT(SendMovement(bool)));
    my_tank = tank;

    tank->setLifeValue(100);
}

Tank *GameEngine::MainTank()
{
    return my_tank;
}

void GameEngine::setConnection(bool is_server, QString ip, int port)
{
    if(is_server) {
        conn_server = new GameServer(port, this);
    } else {
        conn_client = new GameClient(this);
    }

    protocol = new GameProtocol(scene,
                                this,
                                &vehicles,
                                conn_server,
                                conn_client,
                                ip,
                                port);
    this->ip = ip;
    this->port = port;

    if(conn_server) {
        connect(conn_server, SIGNAL(InitConnection(int)), this, SLOT(ServerInitConnection(int)));
        connect(conn_server, SIGNAL(ReceiverMSG(int,QByteArray)), this, SLOT(ServerReceiveMSG(int,QByteArray)));
        CreateTank(true);
    } else if(conn_client) {
        connect(conn_client, SIGNAL(ReceiverMSG(QByteArray)), this, SLOT(ClientReceiveMSG(QByteArray)));
        conn_client->connectToHost(ip, port);
        conn_client->waitForConnected();
    }
}

bool GameEngine::IsServer()
{
    return conn_server==NULL?false:true;
}

QString GameEngine::IpPort()
{
    return QString("%1:%2").arg(ip).arg(port);
}

void GameEngine::ServerInitConnection(int id)
{
    CreateTank();
    protocol->GenerateMap();
}

void GameEngine::ServerReceiveMSG(int id, QByteArray array)
{
    switch (protocol->GetCode(array)) {
        case GameProtocol::CODE_VEHICLE:
            protocol->ReceiverTankStatus(array);
        break;
    }
}

void GameEngine::ClientReceiveMSG(QByteArray array)
{
    switch (protocol->GetCode(array)) {
        case GameProtocol::CODE_MAP:
            protocol->ReceiverMap(array);
        case GameProtocol::CODE_VEHICLE:
            protocol->ReceiverTankStatus(array);
        break;
    }
}






