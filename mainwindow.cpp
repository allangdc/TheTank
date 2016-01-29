#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

#include "gameengine.h"
#include "game_map.h"
#include "vehicle.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    engine = new GameEngine(this);
    engine->setCamera(ui->graphicsView);
    engine->InitScene(":/map/map_tank.tmx");

    setAttribute(Qt::WA_AcceptTouchEvents);
    installEventFilter(ui->btn_left);
    installEventFilter(ui->btn_right);
    installEventFilter(ui->btn_up);

    connect(ui->btn_left, SIGNAL(Pressed()), this, SLOT(ClickLeft()));
    connect(ui->btn_left, SIGNAL(Released()), this, SLOT(ReleaseLeftRight()));
    connect(ui->btn_right, SIGNAL(Pressed()), this, SLOT(ClickRight()));
    connect(ui->btn_right, SIGNAL(Released()), this, SLOT(ReleaseLeftRight()));
    connect(ui->btn_up, SIGNAL(Pressed()), this, SLOT(ClickUp()));
    connect(ui->btn_up, SIGNAL(Released()), this, SLOT(ReleaseUp()));

    ui->btn_left->RotateImage(90);
    ui->btn_right->RotateImage(-90);
    ui->btn_up->RotateImage(180);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClickLeft()
{
    emit MoveTankAction(Vehicle::ROTATE_LEFT);
}

void MainWindow::ReleaseLeftRight()
{
    emit MoveTankAction(Vehicle::STOP);
}

void MainWindow::ClickRight()
{
    emit MoveTankAction(Vehicle::ROTATE_RIGHT);
}

void MainWindow::ClickUp()
{
    emit MoveTankAction(Vehicle::MOVE_UP);
}

void MainWindow::ReleaseUp()
{
    emit MoveTankAction(Vehicle::STOP);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left)
        ClickLeft();
    else if(e->key() == Qt::Key_Right)
        ClickRight();
    else if(e->key() == Qt::Key_Up)
        ClickUp();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
        ReleaseLeftRight();
    else if(e->key() == Qt::Key_Up)
        ReleaseUp();
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    engine->camera->centerOn(0,0);
}


