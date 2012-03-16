#ifndef DEVICEDiscoverySIMPLE_H
#define DEVICEDiscoverySIMPLE_H

#include <QUdpSocket>
#include "deviceinfo.h"

class DeviceDiscoverySimple
{
public:
    DeviceDiscoverySimple();
    bool discoveryOne(int msec, DeviceInfo& dev);

};

#endif // DEVICEDiscoverySIMPLE_H
