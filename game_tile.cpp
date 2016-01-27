#include "game_tile.h"

GameTile::GameTile(int id)
    : QObject(),
      QGraphicsPixmapItem(),
      id(id),
      probability(0),
      current_image_index(-1),
      animation(NULL)
{

}

GameTile::GameTile(const GameTile &tile)
    : GameTile()
{
    id = tile.id;
    probability = tile.probability;
    images = tile.images;
    current_image_index = tile.current_image_index;
    if(tile.animation)
        animation = new QPropertyAnimation(tile.animation->targetObject(),
                                           tile.animation->propertyName());
}

GameTile::~GameTile()
{
    if(animation)
        delete animation;
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
    this->setPixmap(images.at(index).first);
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
