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

    void discovery(int msec);// start async listen devices

    QString& getDeviceList();

signals:
    void newDevice(const QString &info);
    void stoped();


private slots:
    void readDeviceDatagrams();
    void onReady();


protected:
    void processDeviceDatagrams(DeviceInfo* dev);

    QUdpSocket *udpSocket;

};

#endif // DEVICEDISCOVERY_H
