#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVector>

class Tank;
class QWidget;
class GameMap;
class QGraphicsView;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent);
    void setCamera(QGraphicsView *camera);
    void InitScene(QString tmxfile);

    void CreateTank();
    Tank *MainTank();
    QGraphicsView *camera;
    GameMap *scene;
private:
//    QGraphicsView *camera;
//    GameMap *scene;
    QVector<Tank *> tanks;
};

#endif // GAMEENGINE_H
