#include "ipconfigdialog.h"
#include "ui_ipconfigdialog.h"

IPConfigDialog::IPConfigDialog(GameEngine *engine) :
    QDialog(),
    ui(new Ui::IPConfigDialog)
{
    ui->setupUi(this);
    this->engine = engine;

    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    QString ips;
    for(int nIter=0; nIter<list.count(); nIter++)
    {
        if(!list[nIter].isLoopback())
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                if(ips.isEmpty())
                    ips = list[nIter].toString();
                else
                    ips += " | " +list[nIter].toString();
    }
    ui->txt_ip->setText(ips);
    ui->txt_port->setText("9999");
    connect(this,SIGNAL(accepted()),SLOT(UpdateIPPort()));
}

IPConfigDialog::~IPConfigDialog()
{
    delete ui;
}

void IPConfigDialog::UpdateIPPort()
{
    QString ip = ui->txt_ip->text();
    int port = ui->txt_port->text().toInt();
    bool is_server = !ui->rb_client->isChecked();
    engine->setConnection(is_server, ip, port);
}
