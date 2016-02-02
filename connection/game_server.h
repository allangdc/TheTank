#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QTcpServer>
#include <QVector>
#include <QMutex>

class GameSocket;

class GameServer : public QTcpServer
{
    Q_OBJECT
public:
    GameServer(int port, QObject *parent = 0);
    void ReadReady(int id, QByteArray data);
    void SendMessage(int id, QByteArray data);
    void BroadcastMessage(QByteArray data);
    int NumConnections();
private:
    QVector<GameSocket *> sockets;
    QMutex mutex;
signals:
    void InitConnection(int id);
    void ReceiverMSG(int id, QByteArray array);
public slots:
    void NewConnection();
};

#endif // GAMESERVER_H
