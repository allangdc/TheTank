#include "bomb.h"

#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QtMath>

#include "vehicle.h"
#include "game_map.h"

Bomb::Bomb(GameMap *map, Vehicle *vehicle)
    : QObject(vehicle),
      QGraphicsPixmapItem()
{
    this->vehicle = vehicle;
    this->map = map;

    QPixmap pmap = QPixmap(":/tank/image/ball01.png");
    setPixmap(pmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);   //define o ponto de rotação

    animation = new QGraphicsItemAnimation(this);
    animation->setItem(this);
}

void Bomb::Fire()
{
    //QPointF pt;     //position of the bomb
    //pt.setY(this->y() - bomb->pixmap().height()/2);
    //pt.setX(this->x() + this->pixmap().width()/2 - bomb->pixmap().width()/2);

    this->setRotation(vehicle->rotation());
    QPointF pt = mapFromScene(vehicle->pos());
    QPointF me;
    me.setX(pt.x());
    me.setY(pt.y());
    this->setPos(mapFromScene(me));
    map->addItem(this);
    //MoveUp();
}

void Bomb::MoveUp()
{
    if(time_animation) {
        delete time_animation;
        time_animation = NULL;
    }
    time_animation = new QTimeLine(1000, this);
    connect(time_animation, SIGNAL(finished()), this, SLOT(FinishTimeAnimation()));
    connect(time_animation, SIGNAL(valueChanged(qreal)), this, SLOT(MoveTimeAnimation()));
    time_animation->stop();
    time_animation->setDuration(1000);
    time_animation->setFrameRange(0, 120);
    animation->reset();
    animation->setTimeLine(time_animation);
    animation->setTranslationAt(0, 0, 0);
    QPointF np = NextPosition();
    animation->setTranslationAt(1, np.x(), np.y());
    time_animation->setUpdateInterval(20);
    time_animation->setEasingCurve(QEasingCurve::Linear);
    time_animation->start();
}

QPointF Bomb::NextPosition()
{
    qreal d = 100;
    QPointF pt;
    pt.setX(d * qSin(qDegreesToRadians(rotation())));
    pt.setY(-d * qCos(qDegreesToRadians(rotation())));
    return pt;
}

