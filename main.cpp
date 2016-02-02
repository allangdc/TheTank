#include "mainwindow.h"
#include "connection/ipconfigdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    IPConfigDialog ipconfig(w.Engine());

    int ret = ipconfig.exec();
    if(ret == QDialog::Rejected) {
        QApplication::quit();
        exit(0);
    }

#ifndef __ANDROID__
    w.showMaximized();
#else
    w.showFullScreen();
#endif  //__ANDROID__

    return a.exec();
}
