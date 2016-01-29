#include "game_tmx_map.h"

#include <QFile>
#include <QDomDocument>
#include <QDebug>

#include "game_map.h"
#include "game_tiled_set.h"
#include "game_tile.h"
#include "game_map_layer.h"
#include "game_tile_colision.h"

GameTMXMap::GameTMXMap(GameMap *map) : QObject()
{
    this->map = map;
}

bool GameTMXMap::LoadTMXFile(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        return false;
    }
    QDomDocument doc;
    if(!doc.setContent(&file, false)) {
        return false;
    }

    root = doc.documentElement();
    if(root.tagName() != "map")
        return false;

    if(!LoadMapParameters()) {
        return false;
    }

    return true;
}

bool GameTMXMap::LoadMapParameters()
{
    map->setVersion(root.attribute("version").toDouble());
    map->setOrientation(root.attribute("orientation"));
    map->setRenderOrder(root.attribute("renderorder"));
    int width = root.attribute("width").toInt();
    int height = root.attribute("height").toInt();
    map->setMapTileSize(QSize(width, height));
    int tilewidth = root.attribute("tilewidth").toInt();
    int tileheight = root.attribute("tileheight").toInt();
    map->setTileSize(QSize(tilewidth, tileheight));

    for(int i=0; i<root.childNodes().size(); i++) {
        QDomElement e = root.childNodes().at(i).toElement();
        if(e.tagName() == "tileset") {
            if(!LoadTileSetParameters(&e))
                return false;
        } else if(e.tagName() == "layer") {
            if(!LoadLayersParameters(&e))
                return false;
        }
    }

    return true;
}

bool GameTMXMap::LoadTileSetParameters(QDomElement *element)
{
    int firstgid = element->attribute("firstgid").toInt();
    QString name = element->attribute("name");
    int spacing = element->attribute("spacing").toInt();
    int margin = element->attribute("margin").toInt();
    int tilecount = element->attribute("tilecount").toInt();
    int tilewidth = element->attribute("tilewidth").toInt();
    int tileheight = element->attribute("tileheight").toInt();
    GameTiledSet *tiledset = map->LoadTileSet(name,
                                             margin,
                                             spacing,
                                             QSize(tilewidth, tileheight),
                                             firstgid,
                                             tilecount);

    for(int i=0; i<element->childNodes().size(); i++) {
        QDomElement e = element->childNodes().at(i).toElement();
        if(e.tagName() == "image") {
            QString filename = e.attribute("source");
            tiledset->LoadFilename(filename);
        } else if(e.tagName() == "tile") {
            if(!LoadTileParameters(&e))
                return false;
        }
    }
    return true;
}

bool GameTMXMap::LoadTileParameters(QDomElement *element)
{
    int tile_id = element->attribute("id").toInt();
    if(!element->firstChildElement("objectgroup").isNull()) {
        GameTile *tile = map->TileSet()->getTile(tile_id);
        QDomElement obj_group = element->firstChildElement("objectgroup");
        QString draworder = obj_group.attribute("draworder");
        QDomElement obj = obj_group.firstChildElement("object");
        int id = obj.attribute("id").toInt();
        qreal x = obj.attribute("x").toFloat();
        qreal y = obj.attribute("y").toFloat();
        QDomElement pol = obj.firstChildElement("polygon");
        QString points = pol.attribute("points");
        if(!obj.firstChildElement("polygon").isNull()) {
            GameTileColision *colision = new GameTileColision(points);
            colision->setDrawOrder(draworder);
            colision->setPoint(x, y);
            colision->setID(id);
            tile->setColision(colision);
        } else {
            return false;
        }
    }
    //@TODO: Implementar edição de parametros de um GameTile
    return true;
}

bool GameTMXMap::LoadLayersParameters(QDomElement *element)
{
    GameMapLayer *layer = map->addDimension();
    int layer_id = map->TotalLayers()-1;
    QDomElement dt = element->firstChildElement("data").toElement();
    qDebug() << element->firstChildElement("data").isNull();
    if(dt.attribute("encoding") == "csv") {
        QString str = dt.text();
        str.replace("\n", "");
        QStringList list = str.split(",");
        int i=0;
        foreach(QString s, list) {
            map->setValue(s.toInt(), i++, layer_id);
        }
    } else if(!dt.hasAttribute("encoding")) {
        for(int i=0; i<dt.childNodes().size(); i++) {
            QDomElement tile = dt.childNodes().at(i).toElement();
            int id = tile.attribute("gid").toInt();
            map->setValue(id, i++, layer_id);
        }
    }

    layer->setName(element->attribute("name"));
    //int width = element->attribute("width").toInt();
    //int height = element->attribute("height").toInt();
    //layer->setDimension(width, height);
    return true;
}









