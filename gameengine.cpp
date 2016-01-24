#include "gameengine.h"

#include <QGraphicsPixmapItem>
#include <QPixmap>

#include "tank.h"
#include "mainwindow.h"

GameEngine::GameEngine(QWidget *parent)
    : QObject(parent),
      camera(NULL),
      scene(NULL),
      tmx(NULL)
{
}

void GameEngine::setCamera(QGraphicsView *camera)
{
    this->camera = camera;
    camera->scale(3,3);
}

void GameEngine::InitScene(QString tmxfile)
{
    tmx = new TMXFiles();
    tmx->ReadFiles(tmxfile);

    scene = new QGraphicsScene();
    camera->setScene(scene);

    LoadFullMap();

    CreateTank();
    CreateTank();
}

void GameEngine::LoadFullMap()
{
    QSize mapsz = tmx->MapSize();
    scene->setSceneRect(QRect(QPoint(0,0),mapsz));

    int x=0, y=0;
    for(int h = 0; h < mapsz.height(); h += tmx->TiledSize().height()) {
        for(int w = 0; w < mapsz.width(); w += tmx->TiledSize().width()) {
            int id = tmx->MatrixID(0, x++, y);
            if(id>=0) {
                QGraphicsPixmapItem *gpmap = new QGraphicsPixmapItem();
                QPixmap pmap = tmx->TileImageByID(0, id);
                gpmap->setPixmap(pmap);
                scene->addItem(gpmap);
                gpmap->setPos(w, h);
            }
        }
        y++;
        x=0;
    }
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






