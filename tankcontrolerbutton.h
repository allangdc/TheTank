#ifndef TANKCONTROLERBUTTON_H
#define TANKCONTROLERBUTTON_H

#include <QLabel>
#include <QMouseEvent>

#define IMAGE_OFF    ":/buttons/image/arrow_blue.png"
#define IMAGE_ON   ":/buttons/image/arrow_silver.png"
#define IMAGE_SIZE  100

class TankControlerButton : public QLabel
{
    Q_OBJECT
public:
    explicit TankControlerButton(QWidget *parent = 0);
    void RotateImage(qreal angle);
signals:
    void Released();
    void Pressed();

protected:
    bool event(QEvent *e);
    void SetONButton();
    void SetOFFButton();

private:
    qreal image_angle;
};

#endif // TANKCONTROLERBUTTON_H
