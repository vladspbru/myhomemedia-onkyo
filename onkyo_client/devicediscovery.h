#ifndef DEVICEDISCOVERY_H
#define DEVICEDISCOVERY_H

#include <QObject>
#include <QUdpSocket>


class DeviceInfo;

class DeviceDiscovery : public QObject
{
    Q_OBJECT

public:
    explicit DeviceDiscovery(QObject *parent=0);

    // start async listen devices
    void discovery(int msec);
    void discoveryOne(int msec);


signals:
    void error(const QString &message);
    void newDevice(const QString &info);
    void breakTime();


private slots:
    void readDeviceDatagrams();
    void onTime();
    void onError(QAbstractSocket::SocketError socketError);


protected:
    void processDeviceDatagrams(DeviceInfo* dev);

    QUdpSocket *udpSocket;
    bool onlyOne;

};

#endif // DEVICEDISCOVERY_H
