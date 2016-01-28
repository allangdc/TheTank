#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QGraphicsScene>
#include <QVector>
#include <QString>
#include <QSize>

#include "game_tiled_set.h"
#include "game_map_layer.h"

class GameMap : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = 0);
    virtual ~GameMap();
    void setDimension(int x, int y, int total_layers);
    int TotalLayers();
    QSize Dimension(int layer);
    void setMatrixValue(int value, int x, int y, int layer = 0);
    void setMatrixTile(GameTile *tile, int x, int y, int layer = 0);
    QPair<int, GameTile*> Matrix(int x, int y, int layer = 0);
    void setVersion(qreal version);
    void setOrientation(QString orientation);
    void setRenderOrder(QString render_order);
    void setNextObjectID(int next_object_id);
    void setTileSize(QSize size);
    qreal Version();
    QString Orientation();
    QString RenderOrder();
    int NextObjectID();
    QSize TileSize();
    void LoadTileSet(QString filename,
                     int margin,
                     int spacing,
                     QSize tilesize,
                     int firstgid,
                     int tilecount);
    GameTiledSet *TileSet();
private:
    QVector<GameMapLayer *> layers;
    GameTiledSet *tile_set;
    qreal version;
    QString orientation;
    QString render_order;
    QSize tile_size;
    int next_object_id;
};

#endif // GAMEMAP_H
