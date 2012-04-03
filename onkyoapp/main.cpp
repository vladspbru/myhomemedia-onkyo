#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"
#include "onkyo_client_plugin.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    Onkyo_ClientPlugin plug;
    plug.registerTypes("vx.home.qmlcomponents");

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/onkyoapp/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
