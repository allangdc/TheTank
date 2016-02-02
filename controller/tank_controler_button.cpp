#include "controller/tank_controler_button.h"

#include <QEvent>
#include <QTouchEvent>
#include <QDebug>
#include <QPixmap>
#include <QTransform>

TankControlerButton::TankControlerButton(QWidget *parent)
    : QLabel(parent),
      image_angle(0)
{
    setAttribute(Qt::WA_AcceptTouchEvents);

    SetOFFButton();
}

void TankControlerButton::RotateImage(qreal angle)
{
    const QPixmap *pxm = pixmap();
    QTransform trans;
    trans.rotate(angle);
    setPixmap(pxm->transformed(trans));
    image_angle = angle;
}

bool TankControlerButton::event(QEvent *e)
{
#ifdef __ANDROID__
    QTouchEvent *te;
    QList<QTouchEvent::TouchPoint> tps;
    QList<QTouchEvent::TouchPoint>::iterator it;

    switch (e->type()) {
        case QEvent::TouchUpdate:
        case QEvent::TouchEnd:
        case QEvent::TouchBegin:
            te = reinterpret_cast<QTouchEvent *>(e);
            tps = te->touchPoints();
            for(it = tps.begin(); it != tps.end(); it++) {
                if ((*it).state() & Qt::TouchPointPressed ||
                    (*it).state() & Qt::TouchPointMoved) {
                    SetONButton();
                    emit Pressed();
                    return true;
                }
            }
            SetOFFButton();
            emit Released();
            break;
    }
#else
    switch (e->type()) {
        case QEvent::MouseButtonPress:
            SetONButton();
            emit Pressed();
            break;
        case QEvent::MouseButtonRelease:
            SetOFFButton();
            emit Released();
            break;
        default:
            break;
    }

#endif  // __ANDROID__
    return QLabel::event(e);
}

void TankControlerButton::SetONButton()
{
    setPixmap(QPixmap(IMAGE_ON).
              scaled(IMAGE_SIZE,
                     IMAGE_SIZE,
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation));
    RotateImage(image_angle);
}

void TankControlerButton::SetOFFButton()
{
    setPixmap(QPixmap(IMAGE_OFF).
              scaled(IMAGE_SIZE,
                     IMAGE_SIZE,
                     Qt::IgnoreAspectRatio,
                     Qt::SmoothTransformation));
    RotateImage(image_angle);
}
