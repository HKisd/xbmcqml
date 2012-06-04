#ifndef MAIN_H
#define MAIN_H
#include <QtGui/QApplication>
#include <QNetworkAccessManager>
//#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDeclarative>
#include <QSettings>
//#include <QMetaObject>
class XbmcHttp : public QObject
{
    Q_OBJECT
private:
   // QNetworkAccessManager* nam;
    QString settingsFile;
    QString addr;
    QString port;
public:


    XbmcHttp() {
        settingsFile = "/home/user/.config/xbmcqml/xbmchttp.ini";
        loadSettings();
//        addr.append("192.168.1.102");
//        port.append("9090");
    }

    ~XbmcHttp() {
    }

    Q_INVOKABLE void sendKey(const QString &key) {
        QString xbmchttp = "http://" + addr + ":" + port +
                "/xbmcCmds/xbmcHttp?command=SendKey(" + key + ")";
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);
        QNetworkReply* reply = nam->get(QNetworkRequest(xbmchttp));

        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(reply, SIGNAL(readyRead()),reply, SLOT(deleteLater()));

        //qDebug("send!\n");
    }

    Q_INVOKABLE int testConn() {

        //qDebug("send!\n");
        return 0;
    }
    Q_INVOKABLE void loadSettings(){
        QSettings settings(settingsFile, QSettings::NativeFormat);
        addr = settings.value("addr", "").toString();
        port = settings.value("port", "").toString();
    }

    Q_INVOKABLE void saveSettings(){
        QSettings settings(settingsFile, QSettings::NativeFormat);
        settings.setValue("addr", addr);
        settings.setValue("port", port);
    }

    Q_INVOKABLE void setAddr(const QString &newAddr) {
        addr = newAddr;
        qDebug(addr.toAscii());
    }
    Q_INVOKABLE void setPort(const QString &newPort) {
        port = newPort;
        qDebug(port.toAscii());
    }
    Q_INVOKABLE QString getAddr() {
        return addr;
    }
    Q_INVOKABLE QString getPort() {
        return port;
    }

};

#endif // MAIN_H
