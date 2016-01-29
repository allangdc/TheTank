#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVector>

class QWidget;
class GameMap;
class GameCamera;
class Vehicle;

class GameEngine: public QObject
{
    Q_OBJECT
public:
    GameEngine(QWidget *parent);
    void setCamera(GameCamera *camera);
    GameCamera *Camera();
    void InitScene(QString tmxfile);

    void CreateTank();
    Vehicle *MainTank();
private:
    GameCamera *camera;
    GameMap *scene;
    QVector<Vehicle *> vehicles;
};

#endif // GAMEENGINE_H
