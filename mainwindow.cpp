#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <QPropertyAnimation>
#include <QProgressBar>

#include "gameengine.h"
#include "map/game_map.h"
#include "vehicle/vehicle.h"
#include "map/game_camera.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    engine = new GameEngine(this);
    engine->setCamera(ui->graphicsView);
    engine->InitScene(":/map/map_tank.tmx");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFireProgress(int value)
{
    ui->fire_bar->setValue(value);
}

void MainWindow::setLifeProgress(int value)
{
    ui->life_bar->setValue(value);
}

GameEngine *MainWindow::Engine()
{
    return engine;
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

void MainWindow::ClickFire()
{
    emit TankFire();
}

void MainWindow::ReleaseUp()
{
    emit MoveTankAction(Vehicle::STOP);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat()) {
        if(e->key() == Qt::Key_Left)
            ClickLeft();
        else if(e->key() == Qt::Key_Right)
            ClickRight();
        else if(e->key() == Qt::Key_Up)
            ClickUp();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat()) {
        if(e->key() == Qt::Key_Left || e->key() == Qt::Key_Right)
            ReleaseLeftRight();
        else if(e->key() == Qt::Key_Up)
            ReleaseUp();
        else if(e->key() == Qt::Key_Space)
            ClickFire();
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    ui->graphicsView->setCentralizeObject();
}

void MainWindow::showEvent(QShowEvent *e)
{
    ui->lb_status_conection->setText(engine->IsServer()?"Servidor":"Cliente");
    ui->lb_ip_port->setText(engine->IpPort());
}


