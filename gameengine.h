#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVector>
#include "tmxfiles.h"

class Tank;
class QWidget;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent);
    void setCamera(QGraphicsView *camera);
    void InitScene(QString tmxfile);
    void LoadFullMap();

    void CreateTank();
    Tank *MainTank();
private:
    QGraphicsView *camera;
    QGraphicsScene *scene;
    TMXFiles *tmx;
    QVector<Tank *> tanks;
};

#endif // GAMEENGINE_H
