#ifndef OnkyoClient_H
#define OnkyoClient_H

#include <QObject>
#include <QTcpSocket>
#include "iscpmessage.h"

class OnkyoClient : public QObject
{
    Q_OBJECT

public:
    explicit OnkyoClient(const QString &hostName, quint16 port=60128, QObject *parent = 0);
    
    void request(const QString &req);

    bool is_connected();
    void setConnected(bool f);

signals:
    void newStatus(const QString &status);
    void error(const QString &message);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket tcpSocket;
    QString serverName;
    quint16 serverPort;

    QScopedPointer<IscpMessage> curr_status_;
};

#endif // OnkyoClient_H
