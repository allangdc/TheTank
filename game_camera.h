#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <QGraphicsView>
#include <QGraphicsItem>

class GameCamera : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameCamera(QWidget *parent = 0);
    void setCentralizeObject(QGraphicsItem *object = 0);
private:
    QGraphicsItem *center;
signals:

public slots:
};

#endif // GAMECAMERA_H
