#ifndef GAMETILECOLISION_H
#define GAMETILECOLISION_H

#include <QGraphicsPolygonItem>
#include <QString>

#define COLLISION_CODE      0xB0CA

class GameTile;

class GameTileColision : public QGraphicsPolygonItem
{
public:
    explicit GameTileColision(QString list_points, GameTile *tile);
    GameTileColision(const GameTileColision *c);
    virtual ~GameTileColision();
    void setDrawOrder(QString value);
    void setID(int value);
    void setPoint(qreal x, qreal y);
    QString DrawOrder();
    int ID();
    QPointF Point();
    GameTile *Tile();
    QRectF Rect();
    int CodeObject();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {}
private:
    int code;
    GameTile *tile;
    QString draw_order;
    int id;
    QPointF point;
};

#endif // GAMETILECOLISION_H
