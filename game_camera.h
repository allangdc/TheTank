#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPropertyAnimation>

class GameCamera : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QPointF centercamera READ CenterCamera WRITE setCenterCamera)
public:
    explicit GameCamera(QWidget *parent = 0);
    void setCentralizeObject(QGraphicsItem *object = 0);
protected:
    void setCenterCamera(QPointF point);
    QPointF CenterCamera();
    bool event(QEvent *event);
private:
    QPointF center_point;
    QGraphicsItem *center;
    QPropertyAnimation *animation;
signals:
    void Click();
public slots:
};

#endif // GAMECAMERA_H
