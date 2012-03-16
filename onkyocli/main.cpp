#include <QtCore/QCoreApplication>
#include <QTextCodec>
#include <QTimer>
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
    OnkyoClient cli;
    QObject::connect(&cli, SIGNAL( error(QString) ), &prn, SLOT( cerr(QString)) );
    QObject::connect(&cli, SIGNAL( newStatus(QString) ), &prn, SLOT( cout(QString)) );

    if( !opts.host ){
        if( ! cli.init() )
            opts.display_usage_and_exit();
        else
            prn.cout( cli.getDeviceInfo().toString() );
    }
    else {
        DeviceInfo d;
        d.addr = QHostAddress(opts.host);
        d.port = opts.port;
        cli.init(d);
    }

    if( opts.tmdelay > 0)
        QTimer::singleShot( opts.tmdelay, &a, SLOT( quit() ) );

    cli.setConnected(true);
    if(opts.cmd)
        cli.request(opts.cmd);

    return a.exec();
}
