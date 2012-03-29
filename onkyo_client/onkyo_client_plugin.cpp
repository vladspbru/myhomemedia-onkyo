#include "onkyo_client_plugin.h"
#include "onkyoremoteitem.h"
#include "onkyoparameteritem.h"

#include <QtDeclarative/qdeclarative.h>

void Onkyo_ClientPlugin::registerTypes(const char *uri)
{
    // @uri vx.home.qmlcomponents
    qmlRegisterType<OnkyoRemoteItem>(uri, 1, 0, "Onkyo");
    qmlRegisterType<OnkyoParameterItem>(uri, 1, 0, "OnkyoParameter");

    qDebug()<<"Onkyo_ClientPlugin uri: "<<uri;
}

Q_EXPORT_PLUGIN2(Onkyo_Client, Onkyo_ClientPlugin)

