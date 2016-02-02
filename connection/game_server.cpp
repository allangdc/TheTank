#include "connection/game_server.h"
#include "connection/game_socket.h"

#include <QDebug>
#include <QTcpSocket>

GameServer::GameServer(int port, QObject *parent) : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(NewConnection()));

    if(listen(QHostAddress::Any, port)) {
        qDebug() << "Server Started!";
    } else {
        qDebug() << "Server could not start!";
    }
}

void GameServer::ReadReady(int id, QByteArray data)
{
    emit ReceiverMSG(id, data);
}

void GameServer::SendMessage(int id, QByteArray data)
{
    for(QVector<GameSocket *>::iterator it = sockets.begin();
                                        it != sockets.end();
                                        it++) {
        GameSocket *game_socket = *it;
        if(game_socket->ID() == id) {
            QTcpSocket *socket = game_socket->getSocket();
            socket->write(data);
            socket->flush();
            socket->waitForBytesWritten();
            mutex.unlock();
            return;
        }
    }
}

void GameServer::BroadcastMessage(QByteArray data)
{
    for(QVector<GameSocket *>::iterator it = sockets.begin();
                                        it != sockets.end();
                                        it++) {
        GameSocket *game_socket = *it;
        QTcpSocket *socket = game_socket->getSocket();
        socket->write(data);
        socket->flush();
        socket->waitForBytesWritten();
    }
}

int GameServer::NumConnections()
{
    return sockets.size();
}


void GameServer::NewConnection()
{
    static int i = 0;
    GameSocket *game_socket = new GameSocket(nextPendingConnection());
    sockets.push_back(game_socket);
    QTcpSocket *socket = game_socket->getSocket();
    game_socket->setID(++i);
    game_socket->setServer(this);
    emit InitConnection(game_socket->ID());
}

