#ifndef OnkyoClient_H
#define OnkyoClient_H

#include <QObject>
#include <QTcpSocket>
#include "iscpmessage.h"
#include "deviceinfo.h"

class OnkyoClient : public QObject
{
    Q_OBJECT

public:
    explicit OnkyoClient(QObject *parent = 0);

    bool init();// init from discovery service
    void init(const DeviceInfo& d) { dev.addr = d.addr; dev.port = d.port; }

    const DeviceInfo& getDeviceInfo() const { return dev; }

    bool is_connected() const;
    void setConnected(bool f);

    void request(const QString &req);

signals:
    void newStatus(const QString &status);
    void error(const QString &message);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    DeviceInfo  dev;
    QTcpSocket *tcpSocket;

    QScopedPointer<IscpMessage> curr_status_;
};

#endif // OnkyoClient_H
