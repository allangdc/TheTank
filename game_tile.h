#ifndef GAMETILE_H
#define GAMETILE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPair>
#include <QString>
#include <QPropertyAnimation>

#include "tmxfiles.h"

class GameTile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(int show_image READ IndexImage WRITE ShowImage)
public:
    GameTile(int id=0);
    GameTile(const GameTile &tile);
    virtual ~GameTile();
    void addImage(QPixmap *pixmap, QRect region, qreal duration=0);
    void ShowImage(int index = 0);
    int IndexImage();
    qreal Duration(int index);
    void RunAnimation();
    int TotalImages();
    void setProbability(qreal prob);
    qreal Probability();
private:
    int id;
    qreal probability;
    QVector< QPair<QPixmap, qreal> > images;
    int current_image_index;
    QPropertyAnimation *animation;
};

#endif // GAMETILE_H
