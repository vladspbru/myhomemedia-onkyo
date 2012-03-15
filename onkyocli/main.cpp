#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QTimer>
#include "devicediscovery.h"
#include "onkyoclient.h"
#include "cliprinter.h"
#include "options.h"


//-----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);

    Options opts;
    opts.parse_args(argc, argv);

    CliPrinter prn;
    DeviceDiscovery discover;
    OnkyoClient cli;

    if( !opts.host ){ // search AVR
        QObject::connect(&discover, SIGNAL( error(QString) ), &prn, SLOT( cerr(QString)) );
        QObject::connect(&discover, SIGNAL( newDevice(QString) ), &prn, SLOT( cout(QString)) );
        QObject::connect(&discover, SIGNAL( breakTime() ), &a, SLOT( quit() ) );

        if( opts.tmdelay > 0 )
            discover.discoveryOne( opts.tmdelay );
        else {
            discover.discovery( 60*1000 );
        }
    }

    if( opts.host ){
        cli.init(opts.host, opts.port);
        QObject::connect(&cli, SIGNAL( error(QString) ), &prn, SLOT( cerr(QString)) );
        QObject::connect(&cli, SIGNAL( newStatus(QString) ), &prn, SLOT( cout(QString)) );
        QObject::connect(&cli, SIGNAL( breakTime() ), &a, SLOT( quit() ) );
        if(opts.cmd)
             cli.request(opts.cmd);
        else cli.listen(opts.tmdelay);
    }

    return a.exec();
}
