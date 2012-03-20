#include "onkyo_client_plugin.h"
#include "onkyoremoteitem.h"
#include "onkyoparameteritem.h"

#include <QtDeclarative/qdeclarative.h>

void Onkyo_ClientPlugin::registerTypes(const char *uri)
{
    // @uri com.vladspbru.qmlcomponents
    qmlRegisterType<OnkyoRemoteItem>(uri, 1, 0, "Onkyo");
    qmlRegisterType<OnkyoParameterItem>(uri, 1, 0, "OnkyoParameter");

}

Q_EXPORT_PLUGIN2(Onkyo_Client, Onkyo_ClientPlugin)

