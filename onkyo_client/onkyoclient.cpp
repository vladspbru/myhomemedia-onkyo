#include "onkyoclient.h"
#include <QtNetwork>

OnkyoClient::OnkyoClient(const QString &host, quint16 _port, QObject *parent)
    : QObject(parent), tcpSocket(), serverName(host), serverPort(_port), dataSize(0)
{
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onError(QAbstractSocket::SocketError)));
}


void OnkyoClient::onError(QAbstractSocket::SocketError )
{
    emit error( tcpSocket.errorString() );
}

void OnkyoClient::onConnected()
{
    emit newStatus( "" );
}

void OnkyoClient::onDisconnected()
{
    emit newStatus( "" );
}

bool OnkyoClient::is_connected()
{
    return tcpSocket.state() == QAbstractSocket::ConnectedState;
}

void OnkyoClient::setConnected(bool f)
{
    if( f==false )
            tcpSocket.abort();

    if(f){
        if ( tcpSocket.state() == QAbstractSocket::ConnectedState )
                return;
        if ( tcpSocket.state() != QAbstractSocket::UnconnectedState )
            tcpSocket.abort();
        const int Timeout = 5 * 1000;
        tcpSocket.connectToHost(serverName, serverPort);
        if (!tcpSocket.waitForConnected(Timeout))
            emit error( tcpSocket.errorString() );
    }
}

void OnkyoClient::request(const QString &str)
{
    dataSize = 0;

    // reconect if needed
    if ( ! is_connected() ){
        setConnected(true);
        if (! is_connected()) {
            emit error( "Can`t connect to client." );
            return;
        }
    }

    // setup tcp packet
    QByteArray req = str.toUtf8();

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setByteOrder(QDataStream::BigEndian);
    out.writeRawData("ISCP", 4);    //magik
    out << (qint32)16;              //header size
    out << (qint32)0;               //empty data size, see down
    out << (qint8)0x01 << (qint8)0 << (qint8)0 << (qint8)0; // version + 3 reserved
    out.writeRawData( "!1", 2 );
    out.writeRawData( req.begin(), req.size() ); // request messqage
    out << (qint8)0x1A << (qint8)0x0D << (qint8)0x0A; //end
    out.device()->seek(8); //set data size
    out << (quint32)(block.size() - 16);

    tcpSocket.write(block);
}

void OnkyoClient::onReadyRead()
{
    QDataStream in(&tcpSocket);

    if (dataSize == 0) { // get header
        char header[16];
        if (tcpSocket.bytesAvailable() < sizeof(header) )
            return;

        in.readRawData( &header[0], sizeof(header) );
        //check format
        if(
                header[0] != 'I'
                || header[1] != 'S'
                || header[2] != 'C'
                || header[3] != 'P'
                ){
            tcpSocket.abort();
            dataSize = 0;
            emit error( "Bad ISCP format message." );
            return;
        }
        dataSize = qFromBigEndian<qint32>( reinterpret_cast<uchar*>(&header[8]) );
    }

    if (tcpSocket.bytesAvailable() < dataSize)
        return;
    //else get data message
    QByteArray block(dataSize, 0);
    in.readRawData( block.data(), dataSize ) ;
    dataSize = 0;

    if(block.size()>5){
        QString status =  QString::fromUtf8( block.data()+2, block.size()-5 );
        emit newStatus(status);
    }
}
