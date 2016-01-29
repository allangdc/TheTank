#ifndef GAMETILECOLISION_H
#define GAMETILECOLISION_H

#include <QGraphicsPolygonItem>
#include <QString>

class GameTileColision : public QGraphicsPolygonItem
{
public:
    explicit GameTileColision(QString list_points);
    GameTileColision(const GameTileColision *c);
    void setDrawOrder(QString value);
    void setID(int value);
    void setPoint(qreal x, qreal y);
    QString DrawOrder();
    int ID();
    QPointF Point();
private:
    QString draw_order;
    int id;
    QPointF point;
};

#endif // GAMETILECOLISION_H
