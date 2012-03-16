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
        processDeviceDatagrams(&dev);
        if( onlyOne ){
            onTime();
            break;
        }
    }
}

//void DeviceDiscovery::discoveryMcast(int ms)
//{
//        broadcastSocket->bind(QHostAddress::Any, disPort);
//        broadcastSocket->joinMulticastGroup( QHostAddress(disGroup) );
//        broadcastSocket->writeDatagram( qry.bytes(), QHostAddress(disGroup), defOnkyoPort);
//        broadcastSocket->writeDatagram( qry.bytes(), QHostAddress(disGroup), disPort);
//}

void DeviceDiscovery::discovery(int ms)
{
    broadcastSocket = new QUdpSocket(this);
    connect(broadcastSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onError(QAbstractSocket::SocketError)));

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
    onlyOne = false;
}

void DeviceDiscovery::discoveryOne(int msec)
{
    discovery(msec);
    onlyOne = true;
}

void DeviceDiscovery::onTime()
{
    broadcastSocket->disconnect();
    //    broadcastSocket->leaveMulticastGroup( QHostAddress(disGroup) );
    broadcastSocket->deleteLater();
    emit breakTime();
}

void DeviceDiscovery::processDeviceDatagrams(DeviceInfo *dev)
{
    QString info( dev->info.message( ) );
    emit newDevice( info + ";" + dev->addr.toString() );
}

