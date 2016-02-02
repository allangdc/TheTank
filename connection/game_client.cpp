#include "connection/game_client.h"

#include <QDebug>

GameClient::GameClient(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(ReadyRead()));
}

void GameClient::SendMessage(QByteArray data)
{
    this->write(data);
    while(this->waitForBytesWritten());
}

void GameClient::ReadyRead()
{
    QByteArray data = this->readAll();
    emit ReceiverMSG(data);
}

