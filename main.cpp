#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
#ifndef __ANDROID__
    w.show();
#else
    w.showFullScreen();
#endif  //__ANDROID__

    return a.exec();
}
