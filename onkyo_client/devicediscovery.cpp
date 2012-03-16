#include "devicediscovery.h"
#include "deviceinfo.h"
#include "iscpmessage.h"
#include <QTimer>
#include <QNetworkInterface>


//Dynamic Device Discovery params
const char *dddGroup = "239.255.250.250";
const int   dddPort = 9131;

const int defOnkyoPort = 60128;

DeviceDiscovery::DeviceDiscovery(QObject *parent)
    :QObject(parent)
{
    broadcastSocket = new QUdpSocket(this);
    connect(broadcastSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onError(QAbstractSocket::SocketError)));
}

void DeviceDiscovery::onError(QAbstractSocket::SocketError )
{
    emit error( broadcastSocket->errorString() );
}

void DeviceDiscovery::readDeviceDatagrams()
{
    while ( broadcastSocket->hasPendingDatagrams() )  {
        DeviceInfo dev;
        dev.info.bytes().resize(broadcastSocket->pendingDatagramSize());
        broadcastSocket->readDatagram(dev.info.bytes().data(), dev.info.bytes().size(), &dev.addr, &dev.port);
        emit newDevice( dev );
    }
}

void DeviceDiscovery::discovery(int ms)
{
    broadcastSocket->bind();
    connect(broadcastSocket, SIGNAL(readyRead()), this, SLOT(readDeviceDatagrams()));

    IscpMessage qry;
    qry.make_rawcommand("!xECNQSTN");

    QList<QNetworkInterface>	infs = 	QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface, infs){
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            if( !entry.broadcast().isNull() ){
                qDebug() << "IP: " << entry.ip().toString() << "\nNetmask " << entry.netmask().toString() << "\nBroadcast " << entry.broadcast().toString();
                broadcastSocket->writeDatagram( qry.bytes(), entry.broadcast(), defOnkyoPort);
            }
        }
    }

    if( ms > 0 )
        QTimer::singleShot( ms, this, SLOT( onTime() ) );
}

void DeviceDiscovery::stopDiscovery()
{
    broadcastSocket->disconnect();
    broadcastSocket->deleteLater();
}

void DeviceDiscovery::onTime()
{
    stopDiscovery();
    emit breakTime();
}


