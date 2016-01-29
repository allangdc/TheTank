#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class GameEngine;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void ClickLeft();
    void ReleaseLeftRight();
    void ClickRight();
    void ClickUp();
    void ReleaseUp();
signals:
    void MoveTankAction(int code);
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *e);
private:
    Ui::MainWindow *ui;
    GameEngine *engine;
};

#endif // MAINWINDOW_H
