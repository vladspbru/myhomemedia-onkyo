#include "devicediscovery.h"
#include "deviceinfo.h"
#include "iscpmessage.h"
#include <QTimer>


const char *disGroup = "239.255.250.250";
const int disPort = 9131;
const int disBroadcastPort = 60128;


DeviceDiscovery::DeviceDiscovery(QObject *parent)
    :QObject(parent)
{
}

void DeviceDiscovery::readDeviceDatagrams()
{
    while ( udpSocket->hasPendingDatagrams() )  {
        DeviceInfo dev;
        dev.info.bytes().resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(dev.info.bytes().data(), dev.info.bytes().size(), &dev.addr, &dev.port);
        processDeviceDatagrams(&dev);
    }
}

void DeviceDiscovery::discovery(int msec)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, disPort);
    udpSocket->joinMulticastGroup( QHostAddress(disGroup) );

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readDeviceDatagrams()));

    IscpMessage qry;
    qry.make_rawcommand("!xECNQSTN");
    udpSocket->writeDatagram( qry.bytes().data(), qry.bytes().size(),
                                 QHostAddress::Broadcast, disBroadcastPort);

    if( msec > 0 ){
        QTimer::singleShot( msec, this, SLOT( onReady() ) );
    }
}

void DeviceDiscovery::onReady()
{
    udpSocket->disconnect();
    udpSocket->leaveMulticastGroup( QHostAddress(disGroup) );
    udpSocket->deleteLater();
    emit stoped();
}

void DeviceDiscovery::processDeviceDatagrams(DeviceInfo *dev)
{
    QString info( dev->info.message( ) );
    emit newDevice( info + ";" + dev->addr.toString() );
}

