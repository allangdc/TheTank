#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QTcpSocket>
#include <QByteArray>
#include "connection/game_socket.h"

class GameClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
    void SendMessage(QByteArray data);
private:

signals:
    void ReceiverMSG(QByteArray array);

public slots:
    void ReadyRead();
};

#endif // GAMECLIENT_H
