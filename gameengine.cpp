#include "gameengine.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDebug>

#include "tank.h"
#include "mainwindow.h"

GameEngine::GameEngine(QWidget *parent)
    : QObject(parent),
      camera(NULL),
      scene(NULL)
{
}

void GameEngine::setCamera(QGraphicsView *camera)
{
    this->camera = camera;
    camera->scale(2, 2);
}

void GameEngine::InitScene(QString tmxfile)
{
    scene = new GameMap();
    GameTMXMap *tmx = new GameTMXMap(scene);
    qDebug() << "RESULT=" << tmx->LoadTMXFile(tmxfile);
    scene->LoadFullMap();

    camera->setScene(scene);

    CreateTank();
    CreateTank();
}

void GameEngine::CreateTank()
{
    Tank *tank = new Tank(scene);
    if(tanks.size() == 0) {
        MainWindow *mainwindow = reinterpret_cast<MainWindow *>(parent());
        connect(mainwindow, SIGNAL(MoveTankAction(int)), tank, SLOT(MoveAction(int)));
    }
    tanks.push_back(tank);
    scene->addItem(tank);
    tank->setPos(100, 100);
}

Tank *GameEngine::MainTank()
{
    return tanks.at(0);
}






