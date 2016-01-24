#include "tank.h"

#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsView>

Tank::Tank(QGraphicsScene *scene)
    : forward(false),
      rotate(STOP_ROTATION),
      count_steps(0) {
    this->scene = scene;

    QPixmap pmap = QPixmap(":/buttons/image/tank_yellow.png");
    setPixmap(pmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    start(1000.0f / qreal(FRAME_TANK));
}

Tank::Tank(QGraphicsScene *scene, QPointF position, qreal angle) {

}

Tank::~Tank() {

}

void Tank::MoveAction(int code)
{
    switch (code) {
    case FORWARD:
        forward=true;
        break;
    case STOP_FORWARD:
        forward=false;
        break;
    case LEFT:
        rotate = LEFT;
        break;
    case RIGHT:
        rotate = RIGHT;
        break;
    case STOP_ROTATION:
        rotate = STOP_ROTATION;
        break;
    }
}

void Tank::timerEvent(QTimerEvent *e)
{
    if(rotate == LEFT) {
        PulseLeft();
    } else if(rotate == RIGHT) {
        PulseRight();
    }

    if(forward == true) {
        PulseForward();
    }
}

void Tank::PulseForward()
{
    QPointF pt = pos();
    double radian = qDegreesToRadians(rotation());
    pt.setX(pt.x() + STEP_TANK * qSin(radian));
    pt.setY(pt.y() - STEP_TANK * qCos(radian));
    setPos(pt);

    count_steps++;

//    if(count_steps%2 == 0) {
        scene->views().at(0)->centerOn(this);
//    }
}

void Tank::PulseLeft()
{
    setRotation(rotation() - STEP_TANK);
}

void Tank::PulseRight()
{
    setRotation(rotation() + STEP_TANK);
}
