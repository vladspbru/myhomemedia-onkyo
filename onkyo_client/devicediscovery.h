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

public slots:
    void stopDiscovery();

signals:
    void error(const QString &message);
    void newDevice(const DeviceInfo &info);
    void breakTime();


private slots:
    void readDeviceDatagrams();
    void onTime();
    void onError(QAbstractSocket::SocketError socketError);


protected:
    QUdpSocket *broadcastSocket;
};

#endif // DEVICEDISCOVERY_H
