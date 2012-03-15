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
    DeviceDiscovery devdis;

    if( !opts.host ){ // search AVR
        QObject::connect(&devdis, SIGNAL( newDevice(QString) ), &prn, SLOT( cout(QString)) );
        QObject::connect(&devdis, SIGNAL( stoped() ), &a, SLOT( quit() ) );

        if( opts.tmdelay )
            devdis.discovery( opts.tmdelay );
        else {
            devdis.discovery( 60*1000 );
            opts.display_usage_and_exit();
        }
    }
    else {
        OnkyoClient cli(opts.host, opts.port);
        QObject::connect(&cli, SIGNAL( error(QString) ), &prn, SLOT( cerr(QString)) );
        QObject::connect(&cli, SIGNAL( newStatus(QString) ), &prn, SLOT( cout(QString)) );
        if(opts.cmd)
            cli.request(opts.cmd);

        if(opts.spy==0 && opts.tmdelay){
            QTimer::singleShot(opts.tmdelay, &a, SLOT( quit() ));
        }
    }

    return a.exec();
}
