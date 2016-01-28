#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
//#include "tmxfiles.h"

#include "game_tmx_map.h"
#include "game_map.h"

class Tank;
class QWidget;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent);
    void setCamera(QGraphicsView *camera);
    void InitScene(QString tmxfile);

    void CreateTank();
    Tank *MainTank();
private:
    QGraphicsView *camera;
    //QGraphicsScene *scene;
    GameMap *scene;
    //TMXFiles *tmx;
    QVector<Tank *> tanks;
};

#endif // GAMEENGINE_H
