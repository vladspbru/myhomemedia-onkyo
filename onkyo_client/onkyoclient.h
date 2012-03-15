#ifndef OnkyoClient_H
#define OnkyoClient_H

#include <QObject>
#include <QTcpSocket>
#include "iscpmessage.h"

class OnkyoClient : public QObject
{
    Q_OBJECT

public:
    explicit OnkyoClient(QObject *parent = 0);
    void init(const QString &host, quint16 port=60128);
    
    void request(const QString &req, int ms=300);
    void listen(int ms=-1);

    bool is_connected();
    void setConnected(bool f);

signals:
    void newStatus(const QString &status);
    void error(const QString &message);
    void breakTime();

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QString serverName;
    quint16 serverPort;
    QTcpSocket *tcpSocket;

    QScopedPointer<IscpMessage> curr_status_;
};

#endif // OnkyoClient_H
