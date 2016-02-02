#ifndef IPCONFIGDIALOG_H
#define IPCONFIGDIALOG_H

#include <QDialog>
#include <QAbstractSocket>
#include <QNetworkInterface>
#include <QList>

#include "gameengine.h"

namespace Ui {
class IPConfigDialog;
}

class IPConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IPConfigDialog(GameEngine *engine);
    ~IPConfigDialog();
private:
    Ui::IPConfigDialog *ui;
    GameEngine *engine;
public slots:
    void UpdateIPPort();
};

#endif // IPCONFIGDIALOG_H
