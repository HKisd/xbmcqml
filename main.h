#ifndef MAIN_H
#define MAIN_H
#include <QtGui/QApplication>
#include <QNetworkAccessManager>
//#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDeclarative>
#include <QSettings>
#include <qjson/parser.h>
#include <qjson/serializer.h>

//#include <QMetaObject>


class XbmcHttp : public QObject
{
    Q_OBJECT
private:
   // QNetworkAccessManager* nam;
    QString settingsFile;
    QString name;
    QString addr;
    QString port;
    qint32 active;
    struct Server {
        QString name;
        QString addr;
        QString port;
    };
    Server xservers[2];
private slots:
    void replyFinished(QNetworkReply* preply)
    {
        QByteArray replydata = preply->readAll();
        qDebug(replydata);
    }
public:
    XbmcHttp() {
        settingsFile = "/home/user/.config/xbmcqml/xbmchttp2.ini";
        loadSettings();
//        addr.append("192.168.1.102");
//        port.append("9090");
    }

    ~XbmcHttp() {
    }

    Q_INVOKABLE void sendKeyOrg(const QString &key) {
        QString xbmchttp = "http://" + addr + ":" + port +
                "/xbmcCmds/xbmcHttp?command=SendKey(" + key + ")";
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);
        QNetworkReply* reply = nam->get(QNetworkRequest(xbmchttp));

        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(reply, SIGNAL(readyRead()),reply, SLOT(deleteLater()));

        //qDebug("send!\n");
    }

    Q_INVOKABLE void sendKey(const QString &key) {
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);


        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QVariantMap map;
        map.insert("jsonrpc", "2.0");
        map.insert("method", key);

        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        QString dataStr = QString::fromLatin1(data);

        QNetworkReply * reply = nam->post(request, data);
        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }


    Q_INVOKABLE void sendAction(const QString &key) {
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);

        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QVariantMap action;
        QVariantMap map;
        action.insert("action", key);
        map.insert("jsonrpc", "2.0");
        map.insert("method", "Input.ExecuteAction");
        map.insert("params", action);
        map.insert("id", "1");

        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        QString dataStr = QString::fromLatin1(data);

        QNetworkReply * reply = nam->post(request, data);
        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE void sendText(const QString &key) {
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);


        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QVariantMap action;
        QVariantMap map;
        action.insert("text", key);
        map.insert("jsonrpc", "2.0");
        map.insert("method", "Input.SendText");
        map.insert("params", action);

        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        QString dataStr = QString::fromLatin1(data);

        QNetworkReply * reply = nam->post(request, data);
        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE void activateWindow(const QString &key) {
        QNetworkAccessManager *nam = new QNetworkAccessManager(this);


        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QVariantMap action;
        QVariantMap map;
        action.insert("window", key);
        map.insert("jsonrpc", "2.0");
        map.insert("method", "GUI.ActivateWindow");
        map.insert("params", action);

        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        QString dataStr = QString::fromLatin1(data);

        QNetworkReply * reply = nam->post(request, data);
        connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE int testConn() {

        //qDebug("send!\n");
        return 0;
    }
    Q_INVOKABLE void loadSettings(){
        QSettings settings(settingsFile, QSettings::NativeFormat);
        active = settings.value("active", "").toInt();
        int size = settings.beginReadArray("servers");
        for (int i = 0; i < size; ++i) {
             settings.setArrayIndex(i);
             xservers[i].name = settings.value("name").toString();
             xservers[i].addr = settings.value("addr").toString();
             xservers[i].port = settings.value("port").toString();
        }
        settings.endArray();
        if (size > 0) {
            name = xservers[active].name;
            addr = xservers[active].addr;
            port = xservers[active].port;
        } else {
            name = "";
            addr = "";
            port = "";
        }
    }

    Q_INVOKABLE void saveSettings(){
        QSettings settings(settingsFile, QSettings::NativeFormat);
        /*settings.setValue("addr", addr);
        settings.setValue("port", port);*/
        settings.setValue("active", active);
        settings.beginWriteArray("servers");
        //int size=sizeof(xservers)/sizeof(Server);
        int size = 2;
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            /*settings.setValue("name", list.at(i).name);
            settings.setValue("addr", list.at(i).addr);
            settings.setValue("port", list.at(i).port);*/
            settings.setValue("name", xservers[i].name);
            settings.setValue("addr", xservers[i].addr);
            settings.setValue("port", xservers[i].port);
        }
        settings.endArray();
    }

    Q_INVOKABLE void setName(const QString &newName) {
        name = newName;
        xservers[active].name = newName;
        qDebug(name.toAscii());
    }
    Q_INVOKABLE void setAddr(const QString &newAddr) {
        addr = newAddr;
        xservers[active].addr = newAddr;
        qDebug(addr.toAscii());
    }
    Q_INVOKABLE void setPort(const QString &newPort) {
        port = newPort;
        xservers[active].port = newPort;
        qDebug(port.toAscii());
    }

    Q_INVOKABLE QString getNameByIdx(qint32 idx) {
        return xservers[idx].name;
    }

    Q_INVOKABLE QString getName() {
        return xservers[active].name;
    }
    Q_INVOKABLE QString getAddr() {
        return xservers[active].addr;
    }
    Q_INVOKABLE QString getPort() {
        return xservers[active].port;
    }
    Q_INVOKABLE void setActive(const qint32 act) {
        active = act;
        qDebug() << active;
        name = xservers[active].name;
        addr = xservers[active].addr;
        port = xservers[active].port;
        saveSettings();
    }
    Q_INVOKABLE qint32 getActive() {
        return active;
    }
};

#endif // MAIN_H
