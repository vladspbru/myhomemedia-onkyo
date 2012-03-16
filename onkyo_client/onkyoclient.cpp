#include "onkyoclient.h"
#include "iscpmessage.h"
#include "devicediscoverysimple.h"
#include "deviceinfo.h"
#include <QtNetwork>

OnkyoClient::OnkyoClient(QObject *parent)
    : QObject(parent)
{
}

bool OnkyoClient::init()
{
    serverName = "";
    serverPort = 0;

    DeviceDiscoverySimple discover;
    DeviceInfo      dev;
    if( !discover.discoveryOne( 1000, dev ) ) {
        emit error( "No Onkyo on net!." );
        return false;
    }
    init(dev.addr.toString(), dev.port);
    return true;
}

void OnkyoClient::init(const QString &host, quint16 port)
{
    tcpSocket = new QTcpSocket(this);
    serverName= host;
    serverPort = port;
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onError(QAbstractSocket::SocketError)));
}


void OnkyoClient::onError(QAbstractSocket::SocketError )
{
    emit error( tcpSocket->errorString() );
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
    return tcpSocket->state() == QAbstractSocket::ConnectedState;
}

void OnkyoClient::setConnected(bool f)
{
    if( f==false )
        tcpSocket->abort();

    if(f){
        if ( tcpSocket->state() == QAbstractSocket::ConnectedState )
            return;
        if ( tcpSocket->state() != QAbstractSocket::UnconnectedState )
            tcpSocket->abort();
        const int Timeout = 3 * 1000;
        tcpSocket->connectToHost(serverName, serverPort);
        if (!tcpSocket->waitForConnected(Timeout))
            emit error( tcpSocket->errorString() );
    }
}

void OnkyoClient::listen(int ms)
{
    curr_status_.reset(0);
    // reconect if needed
    if ( ! is_connected() ){
        setConnected(true);
        if (! is_connected()) {
            emit error( "Can`t connect to client." );
            return;
        }
    }

    if( ms > 0 )
        QTimer::singleShot( ms, this, SIGNAL( breakTime() ) );
}

void OnkyoClient::request(const QString &str, int ms)
{
    listen(ms);
    IscpMessage cmd;
    tcpSocket->write( cmd.make_command(str) );
}

void OnkyoClient::onReadyRead()
{
    QDataStream in(tcpSocket);

    if ( curr_status_.isNull() ) { // get header
        if (tcpSocket->bytesAvailable() < IscpMessage::header_size )
            return;

        char header[ IscpMessage::header_size ];
        in.readRawData( &header[0], IscpMessage::header_size );
        //check format
        if(
                header[0] != 'I'
                || header[1] != 'S'
                || header[2] != 'C'
                || header[3] != 'P'
                ){
            curr_status_.reset(0);
            tcpSocket->abort();
            emit error( "Bad ISCP format message." );
            return;
        }
        quint32 dataSize = qFromBigEndian<qint32>( reinterpret_cast<uchar*>(&header[8]) );

        curr_status_.reset( new IscpMessage( dataSize ) );
        curr_status_->bytes().prepend( header, sizeof(header) );
    }

    if (tcpSocket->bytesAvailable() < curr_status_->message_size() )
        return;
    //else get data message
    in.readRawData( curr_status_->message(), curr_status_->message_size() ) ;

    if( curr_status_->message_size() > 2 ){
        QString status =  QString::fromUtf8( curr_status_->message()+2, curr_status_->message_size()-2 );
        emit newStatus(status);
    }
    curr_status_.reset(0);
}
