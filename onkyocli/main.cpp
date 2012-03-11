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
    if( !opts.host )
            opts.display_usage_and_exit();

    CliPrinter prn;
    OnkyoClient cli(opts.host, opts.port);

    QObject::connect(&cli, SIGNAL( error(QString) ), &prn, SLOT( cerr(QString)) );
    QObject::connect(&cli, SIGNAL( newStatus(QString) ), &prn, SLOT( cout(QString)) );

    if(opts.cmd)
        cli.request(opts.cmd);

    if(opts.spy==0 && opts.tmdelay){
        QTimer::singleShot(opts.tmdelay, &a, SLOT( quit() ));
    }

    return a.exec();
}
