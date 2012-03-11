#ifndef ONKYO_CLIENT_PLUGIN_H
#define ONKYO_CLIENT_PLUGIN_H

#include <QtDeclarative/QDeclarativeExtensionPlugin>

class Onkyo_ClientPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
    
public:
    void registerTypes(const char *uri);
};

#endif // ONKYO_CLIENT_PLUGIN_H

