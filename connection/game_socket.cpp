#include "connection/game_socket.h"
#include "connection/game_server.h"

#include <QTcpSocket>

GameSocket::GameSocket(): QObject()
{
    socket = new QTcpSocket();
    server = NULL;
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

GameSocket::GameSocket(QTcpSocket *socket, QObject *parent): QObject(parent)
{
    this->socket = socket;
    server = NULL;
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

void GameSocket::setID(int value)
{
    id = value;
}

int GameSocket::ID()
{
    return id;
}

void GameSocket::setServer(GameServer *server)
{
    this->server = server;
}

QTcpSocket *GameSocket::getSocket()
{
    return socket;
}

void GameSocket::ReadyRead()
{
    QByteArray data = socket->readAll();
    server->ReadReady(id, data);
}

