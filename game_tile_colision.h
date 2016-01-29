#ifndef GAMETILECOLISION_H
#define GAMETILECOLISION_H

#include <QGraphicsPolygonItem>
#include <QString>

#define COLLISION_CODE      12345

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
    int code;
    GameTile *Tile();
    QRectF Rect();
private:
    GameTile *tile;
    QString draw_order;
    int id;
    QPointF point;
};

#endif // GAMETILECOLISION_H
