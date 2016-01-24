#ifndef TANK_H
#define TANK_H

#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimerEvent>

#define VELOCITY_TANK       50.0f //pixel/sec
#define FRAME_TANK          60
#define STEP_TANK           VELOCITY_TANK/FRAME_TANK

class QGraphicsScene;

class Tank : public QTimer, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    enum move_direction {FORWARD, LEFT, RIGHT, STOP_ROTATION, STOP_FORWARD};

    explicit Tank(QGraphicsScene *scene);
    Tank(QGraphicsScene *scene, QPointF position, qreal angle);
    virtual ~Tank();

signals:

public slots:
    void MoveAction(int code);
protected:
    QGraphicsScene *scene;
    void timerEvent(QTimerEvent *e);
private:
    void PulseForward();
    void PulseLeft();
    void PulseRight();
    int rotate;
    bool forward;
    long count_steps;
};

#endif // TANK_H
