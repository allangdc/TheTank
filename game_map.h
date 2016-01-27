#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QGraphicsScene>
#include <QVector>

class GameMap : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = 0);
    void setDimension(int x, int y);
    QSize Dimension();
    void setMatrixValue(int x, int y, int value);
    int MatrixValue(int x, int y);
private:
    QVector< QVector<int> > map_id;
};

#endif // GAMEMAP_H
