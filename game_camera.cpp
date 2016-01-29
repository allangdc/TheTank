#include "game_camera.h"

#include <QDebug>
#include <QtMath>

GameCamera::GameCamera(QWidget *parent)
    : QGraphicsView(parent),
      center(NULL)
{
    scale(1,1);
}

void GameCamera::setCentralizeObject(QGraphicsItem *object)
{
    center = object;
}
