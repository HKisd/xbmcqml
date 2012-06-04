#include <QtGui/QApplication>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDeclarative>
#include <QMetaObject>

#include "qmlapplicationviewer.h"
#include "main.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer>viewer(QmlApplicationViewer::create());
    XbmcHttp xbmcHttp;
    QDeclarativeContext *ctxt = viewer->rootContext();
    ctxt->setContextProperty("xbmcHttp", &xbmcHttp);
    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/xbmcqml/main.qml"));
    //qmlRegisterType<GConfItemQmlProxy>("MeeGoSettings", 1, 0, "GConfItem");
    viewer->showExpanded();
    //qDebug("main\n");
    return app->exec();
}
