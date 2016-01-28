#include "game_tmx_map.h"

#include <QFile>
#include <QDomDocument>

#include "game_map.h"

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
    int tilewidth = root.attribute("tilewidth").toInt();
    int tileheight = root.attribute("tileheight").toInt();
    map->setTileSize(QSize(tilewidth, tileheight));

    for(int i=0; i<root.childNodes().size(); i++) {
        QDomElement e = root.childNodes().at(i).toElement();
        if(e.tagName() == "tileset") {
            if(!LoadTileSetParameters(&e))
                return false;
        } else if(e.tagName() == "layer") {
//            Layer l;
//            l.Load(&e);
//            layers.push_back(l);
        }
    }
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
    map->LoadTileSet(name,
                     margin,
                     spacing,
                     QSize(tilewidth, tileheight),
                     firstgid,
                     tilecount);

    for(int i=0; i<element->childNodes().size(); i++) {
        QDomElement e = element->childNodes().at(i).toElement();
        if(e.tagName() == "tile") {
            if(!LoadTileParameters(&e))
                return false;
        }
    }
}

bool GameTMXMap::LoadTileParameters(QDomElement *element)
{
    //@TODO: Implementar edição de parametros de um GameTile
}









