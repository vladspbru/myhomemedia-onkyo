#include "devicediscoverysimple.h"
#include "iscpmessage.h"
#include <QNetworkInterface>

DeviceDiscoverySimple::DeviceDiscoverySimple()
{
}


bool DeviceDiscoverySimple::discoveryOne(int msec, DeviceInfo& dev)
{
    QScopedPointer<QUdpSocket> broadcastSocket( new QUdpSocket() );
    broadcastSocket->bind();

    // send broadcast query on all interfaces
    IscpMessage qry;
    qry.make_rawcommand("!xECNQSTN");
    QList<QNetworkInterface>	infs = 	QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface, infs){
        foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
            if( !entry.broadcast().isNull() ){
                broadcastSocket->writeDatagram( qry.bytes(), entry.broadcast(), 60128);
            }
        }
    }

    if( broadcastSocket->waitForReadyRead(msec) )
        while ( broadcastSocket->hasPendingDatagrams() )  {
            dev.info.bytes().resize(broadcastSocket->pendingDatagramSize());
            broadcastSocket->readDatagram(dev.info.bytes().data(), dev.info.bytes().size(), &dev.addr, &dev.port);
            return true;
        }
    return false;
}
