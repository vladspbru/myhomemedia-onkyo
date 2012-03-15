#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <QHostAddress>
#include <QByteArray>
#include "iscpmessage.h"

class DeviceInfo
{
public:
    DeviceInfo(): addr(), port(), info() {}

    QHostAddress addr;
    quint16      port;
    IscpMessage  info;
};


#endif // DEVICEINFO_H
