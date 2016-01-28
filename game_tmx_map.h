#ifndef GAMETMXMAP_H
#define GAMETMXMAP_H

#include <QObject>
#include <QString>
#include <QDomElement>

class GameMap;

class GameTMXMap : public QObject
{
    Q_OBJECT
public:
    explicit GameTMXMap(GameMap *map);
    bool LoadTMXFile(QString filename);
private:
    bool LoadMapParameters();
    bool LoadTileSetParameters(QDomElement *element);
    bool LoadTileParameters(QDomElement *element);
    GameMap *map;
    QDomElement root;
};

#endif // GAMETMXMAP_H
