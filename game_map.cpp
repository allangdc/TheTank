#include "game_map.h"

GameMap::GameMap(QObject *parent)
    : QGraphicsScene(parent),
      tile_set(NULL)
{

}

GameMap::~GameMap()
{
    if(tile_set)
        delete tile_set;
    for(int i=0; i<layers.size(); i++)
        delete layers.at(i);
}

void GameMap::setDimension(int x, int y, int total_layers)
{
    for(int i=0; i<total_layers; i++) {
        GameMapLayer *layer = new GameMapLayer(this);
        layer->setDimension(x, y);
        layers.push_back(layer);
    }
}

int GameMap::TotalLayers()
{
    return layers.size();
}

QSize GameMap::Dimension(int layer)
{
    return layers.at(layer)->Dimension();
}

void GameMap::setMatrixValue(int value, int x, int y, int layer)
{
    layers.at(layer)->setMatrixValue(value, x, y);
}

void GameMap::setMatrixTile(GameTile *tile, int x, int y, int layer)
{
    layers.at(layer)->setMatrixTile(tile, x, y);
}

QPair<int, GameTile *> GameMap::Matrix(int x, int y, int layer)
{
    return layers.at(layer)->Matrix(x, y);
}

void GameMap::setVersion(qreal version)
{
    this->version = version;
}

void GameMap::setOrientation(QString orientation)
{
    this->orientation = orientation;
}

void GameMap::setRenderOrder(QString render_order)
{
    this->render_order = render_order;
}

void GameMap::setNextObjectID(int next_object_id)
{
    this->next_object_id = next_object_id;
}

void GameMap::setTileSize(QSize size)
{
    this->tile_size = size;
}

int GameMap::NextObjectID()
{
    return next_object_id;
}

QSize GameMap::TileSize()
{
    return tile_size;
}

qreal GameMap::Version()
{
    return version;
}

QString GameMap::Orientation()
{
    return orientation;
}

QString GameMap::RenderOrder()
{
    return render_order;
}

void GameMap::LoadTileSet(QString filename,
                          int margin,
                          int spacing,
                          QSize tilesize,
                          int firstgid,
                          int tilecount)
{
    if(tile_set)
        delete tile_set;
    tile_set = new GameTiledSet(filename,
                                margin,
                                spacing,
                                tilesize,
                                firstgid,
                                tilecount);
}

GameTiledSet *GameMap::TileSet()
{
    return tile_set;
}
