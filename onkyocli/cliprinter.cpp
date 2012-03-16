#include "cliprinter.h"
#include <QDebug>
#include <iostream>

CliPrinter::CliPrinter(QObject *parent) :
    QObject(parent)
{
}

void CliPrinter::cout(const QString& str)
{
    if(!str.isEmpty()){
        std::cout<<str.simplified().toLocal8Bit().constData()<<std::endl;
    }
}

void CliPrinter::cerr(const QString& str)
{
    std::cerr<<qPrintable( str.simplified() )<<std::endl;
}
