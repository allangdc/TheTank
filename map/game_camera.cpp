#include "map/game_camera.h"

#include <QDebug>
#include <QtMath>
#include <QEvent>
#include <QTouchEvent>

GameCamera::GameCamera(QWidget *parent)
    : QGraphicsView(parent),
      center(NULL)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    scale(1,1);
//    animation = new QPropertyAnimation(this, "centercamera");
//    animation->setDuration(1000);
    //animation->setEasingCurve(QEasingCurve::Linear);
    this->setViewportUpdateMode(NoViewportUpdate);
}

void GameCamera::setCentralizeObject(QGraphicsItem *object)
{
    if(object) {
        center = object;
        centerOn(center);
        center_point = center->pos();
    }
    this->centerOn(center);
//    if(animation->currentTime() == 0 || animation->currentTime() >= 1000) {
//        animation->setStartValue(center_point);
//        animation->setEndValue(center->pos());
//        animation->start();
//    }
}

void GameCamera::setCenterCamera(QPointF point)
{
    center_point = point;
    centerOn(center_point);
}

QPointF GameCamera::CenterCamera()
{
    return center_point;
}

bool GameCamera::event(QEvent *event)
{
#ifdef __ANDROID__
    QTouchEvent *te;
    QList<QTouchEvent::TouchPoint> tps;
    QList<QTouchEvent::TouchPoint>::iterator it;

    switch (event->type()) {
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::TouchBegin:
            te = reinterpret_cast<QTouchEvent *>(event);
            tps = te->touchPoints();
            for(it = tps.begin(); it != tps.end(); it++) {
                if ((*it).state() & Qt::TouchPointPressed ||
                    (*it).state() & Qt::TouchPointMoved) {
                    emit Click();
                    return true;
                }
            }
            break;
    }
#else
    switch (event->type()) {
        case QEvent::MouseButtonPress:
            emit Click();
            break;
    }

#endif  // __ANDROID__
    return QGraphicsView::event(event);
}



