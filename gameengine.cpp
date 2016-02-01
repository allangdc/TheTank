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

    Tank *v = CreateTank();
    MainWindow *mainwindow = reinterpret_cast<MainWindow *>(parent());
    camera->setCentralizeObject(v);
    connect(mainwindow, SIGNAL(MoveTankAction(int)), v, SLOT(MoveVehicle(int)));
    connect(mainwindow, SIGNAL(TankFire()), v, SLOT(Fire()));
    connect(v, SIGNAL(sigFireValue(int)), mainwindow, SLOT(setFireProgress(int)));
    connect(v, SIGNAL(sigLifeValue(int)), mainwindow, SLOT(setLifeProgress(int)));
    connect(camera, SIGNAL(Click()), v, SLOT(Fire()));
    camera->setCentralizeObject(v);
    v->setFireValue(100);
    v->setLifeValue(100);

    CreateTank();
}

Tank *GameEngine::CreateTank()
{
    static int i=0;
    Tank *v = new Tank(scene, i++);
    scene->addItem(v);
    v->setRandPos();
    v->setRandRotation();
    return v;
}

Vehicle *GameEngine::MainTank()
{
    return vehicles.at(0);
}






