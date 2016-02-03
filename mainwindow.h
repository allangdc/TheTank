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
    GameEngine *Engine();
    void ClearSummary();
    void AddSummary(QString tank, int shot, int hit, int death);
public slots:
    void ClickLeft();
    void ReleaseLeftRight();
    void ClickRight();
    void ClickUp();
    void ClickFire();
    void ReleaseUp();
    void setFireProgress(int value);
    void setLifeProgress(int value);
    void SwapSummary();
signals:
    void MoveTankAction(int code);
    void TankFire();
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *e);
    void showEvent(QShowEvent *e);
private:
    Ui::MainWindow *ui;
    GameEngine *engine;
};

#endif // MAINWINDOW_H
