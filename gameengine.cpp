#include "gameengine.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

#include "game_tmx_map.h"
#include "game_map.h"
#include "mainwindow.h"
#include "vehicle.h"
#include "game_camera.h"

GameEngine::GameEngine(QWidget *parent)
    : QObject(parent),
      camera(NULL),
      scene(NULL)
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

    CreateTank();
}

void GameEngine::CreateTank()
{
//    Tank *tank = new Tank(scene);
//    if(tanks.size() == 0) {
        MainWindow *mainwindow = reinterpret_cast<MainWindow *>(parent());
//        connect(mainwindow, SIGNAL(MoveTankAction(int)), tank, SLOT(MoveAction(int)));
//    }
//    tanks.push_back(tank);
//    scene->addItem(tank);
//    tank->setPos(100, 100);
    Vehicle *v = new Vehicle(scene);
    camera->setCentralizeObject(v);
    connect(mainwindow, SIGNAL(MoveTankAction(int)), v, SLOT(MoveVehicle(int)));
    scene->addItem(v);
    camera->centerOn(v);
}

Vehicle *GameEngine::MainTank()
{
    return vehicles.at(0);
}






