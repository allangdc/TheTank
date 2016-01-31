#include "game_map.h"

#include <QDebug>
#include <QPixmap>
#include <QPainter>

#include "game_tiled_set.h"
#include "game_tile_colision.h"
#include "game_map_layer.h"
#include "game_tile.h"

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
        addDimension(x, y);
    }
}

void GameMap::setDimension(int total_layers)
{
    for(int i=0; i<total_layers; i++) {
        addDimension();
    }
}

GameMapLayer *GameMap::addDimension(int x, int y)
{
    GameMapLayer *layer = new GameMapLayer(this);
    layer->setDimension(x, y);
    layers.push_back(layer);
    return layer;
}

GameMapLayer *GameMap::addDimension()
{
    GameMapLayer *layer = new GameMapLayer(this);
    layer->setDimension(MapTileSize().width(), MapTileSize().height());
    layers.push_back(layer);
    return layer;
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

void GameMap::setValue(int value, int item, int layer)
{
    layers.at(layer)->setValue(value, item);
}

void GameMap::setMatrixTile(GameTile *tile, int x, int y, int layer)
{
    layers.at(layer)->setMatrixTile(tile, x, y);
}

void GameMap::setTile(GameTile *tile, int item, int layer)
{
    layers.at(layer)->setTile(tile, item);
}

QPair<int, GameTile *> GameMap::Matrix(int x, int y, int layer)
{
    return layers.at(layer)->Matrix(x, y);
}

QPair<int, GameTile *> GameMap::Item(int item, int layer)
{
    return layers.at(layer)->Item(item);
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

void GameMap::setMapTileSize(QSize size)
{
    map_tile_size = size;
}

int GameMap::NextObjectID()
{
    return next_object_id;
}

QSize GameMap::TileSize()
{
    return tile_size;
}

QSize GameMap::MapTileSize()
{
    return map_tile_size;
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

GameTiledSet *GameMap::LoadTileSet(QString name,
                          int margin,
                          int spacing,
                          QSize tilesize,
                          int firstgid,
                          int tilecount)
{
    if(tile_set)
        delete tile_set;
    tile_set = new GameTiledSet(name,
                                margin,
                                spacing,
                                tilesize,
                                firstgid,
                                tilecount);
    return tile_set;
}

GameTiledSet *GameMap::TileSet()
{
    return tile_set;
}

void GameMap::LoadFullMap(int layer)
{
    GameTiledSet *set = TileSet();
    int maxi = Dimension(layer).width() * Dimension(layer).height();
    for(int i=0; i<maxi; i++) {
        int id = Item(i, layer).first - set->FirstGid();
        GameTile *tile = new GameTile(set->getTile(id));
        setTile(tile, i, layer);
        this->addItem(tile);
        GameTileColision *colision = tile->Colision();
        if(colision) {
            tile->UpdateTileColisionPos();
            this->addItem(colision);
        }
    }
}

void GameMap::LoadRectMap(QRect region, int layer)
{
    GameTiledSet *set = TileSet();
    int maxi = Dimension(layer).width() * Dimension(layer).height();
    for(int i=0; i<maxi; i++) {
        int x, y;
        y = i / Dimension(layer).width();
        x = i - y*Dimension(layer).width();
        QPair<int, GameTile *> pair = this->Item(i, layer);
        if(region.contains(x, y)) {
            if(!pair.second) {
                int id = Item(i, layer).first - set->FirstGid();
                GameTile *tile = new GameTile(set->getTile(id));
                setTile(tile, i, layer);
                this->addItem(tile);
            }
        } else {
            if(pair.second) {
                GameTile *tile = pair.second;
                this->removeItem(tile);
                delete tile;
                setTile(NULL, i, layer);
            }
        }
    }
}


