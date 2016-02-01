#include "map/game_tile.h"

#include <QPropertyAnimation>

#include "map/game_tile_colision.h"

GameTile::GameTile(int id)
    : QObject(),
      QGraphicsPixmapItem(),
      id(id),
      probability(0),
      current_image_index(-1),
      animation(NULL),
      colision(NULL)
{

}

GameTile::GameTile(const GameTile *tile)
    : GameTile(0)
{
    if(tile) {
        id = tile->id;
        probability = tile->probability;
        images = tile->images;
        current_image_index = tile->current_image_index;
        this->setPixmap(tile->pixmap());
        if(tile->animation)
            animation = new QPropertyAnimation(tile->animation->targetObject(),
                                               tile->animation->propertyName());
        if(tile->colision)
            colision = new GameTileColision(tile->colision);
    }
}

GameTile::GameTile(const GameTile &tile)
    : GameTile(0)
{
    id = tile.id;
    probability = tile.probability;
    images = tile.images;
    current_image_index = tile.current_image_index;
    this->setPixmap(tile.pixmap());
    if(tile.animation)
        animation = new QPropertyAnimation(tile.animation->targetObject(),
                                           tile.animation->propertyName());
    if(tile.colision)
        colision = new GameTileColision(tile.colision);
}

GameTile::~GameTile()
{
    if(animation)
        delete animation;
    if(colision)
        delete colision;
}

void GameTile::addImage(QPixmap *pixmap,
                        QRect region,
                        qreal duration)
{
    QPixmap pxm = pixmap->copy(region);
    images.push_back(QPair<QPixmap,qreal>(pxm, duration));
    if(images.size() == 1) {
        ShowImage(0);
    }
}

void GameTile::ShowImage(int index)
{
    current_image_index = index;
    QGraphicsPixmapItem::setPixmap(images.at(index).first);
}

int GameTile::IndexImage()
{
    return current_image_index;
}

qreal GameTile::Duration(int index)
{
    return images.at(index).second;
}

void GameTile::RunAnimation()
{
    if(!animation) {
        animation = new QPropertyAnimation(this, "show_image");
    }
    qreal sum = 0;
    for(int i=0; i<TotalImages(); i++) {
        sum += Duration(i);
    }
    animation->setDuration(sum);
    animation->setLoopCount(-1);
    animation->start();
}

int GameTile::TotalImages()
{
    return images.size();
}

void GameTile::setProbability(qreal prob)
{
    probability = prob;
}

qreal GameTile::Probability()
{
    return probability;
}

void GameTile::setColision(GameTileColision *colision)
{
    this->colision = colision;
}

GameTileColision *GameTile::Colision()
{
    return colision;
}

void GameTile::UpdateTileColisionPos()
{
    int x = this->pos().x() + colision->pos().x();
    int y = this->pos().y() + colision->pos().y();
    colision->setPos(x, y);
}
