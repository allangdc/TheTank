#ifndef GAMESOCKET_H
#define GAMESOCKET_H

#include <QObject>

class GameServer;
class QTcpSocket;

class GameSocket: public QObject
{
    Q_OBJECT
public:
    GameSocket();
    GameSocket(QTcpSocket *socket, QObject *parent = NULL);
    void setID(int value);
    int ID();
    void setServer(GameServer *server);
    QTcpSocket *getSocket();
private:
    int id;
    QTcpSocket *socket;
    GameServer *server;
public slots:
    void ReadyRead();
};

#endif // GAMESOCKET_H
