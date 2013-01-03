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
    QNetworkAccessManager *nam;


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
        qDebug("replyFinished2");
        qDebug(replydata);
    }

    void parseVolume(QNetworkReply* preply)
    {
        QByteArray replydata = preply->readAll();
        QJson::Parser driver;
        bool ok;
        QVariantMap result = driver.parse (replydata, &ok).toMap();
        if (!ok) {
          qDebug("An error occured during parsing");
          return;
          //exit (1);
        }
        QVariantMap nestedMap = result["result"].toMap();
        qDebug("parseVolume");
        qDebug() << nestedMap;
        if(nestedMap.count() < 1)
            return;
        qint32 volume = nestedMap["volume"].toInt();

        qDebug(replydata);
        qDebug() << volume;
        serverVolume = volume;
    }

private:
    void delay()
    {
        QTime dieTime= QTime::currentTime().addSecs(1);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }


public:
    qint32 serverVolume;
    XbmcHttp() {
        settingsFile = "/home/user/.config/xbmcqml/xbmchttp2.ini";
        loadSettings();
        serverVolume = -1;
        nam = new QNetworkAccessManager(this);
        connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseVolume(QNetworkReply*)));
    }

    ~XbmcHttp() {
    }

    Q_INVOKABLE void sendKey(const QString &key) {
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
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));

    }


    Q_INVOKABLE void sendAction(const QString &key) {
        //QNetworkAccessManager *nam = new QNetworkAccessManager(this);

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
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        //connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE void sendText(const QString &key) {
        //QNetworkAccessManager *nam = new QNetworkAccessManager(this);


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
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        //connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE void activateWindow(const QString &key) {
        //QNetworkAccessManager *nam = new QNetworkAccessManager(this);


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
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        //connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
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
        /*name = "PC";
        addr = "192.168.0.50";
        port = "8080";*/
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
    Q_INVOKABLE qint32 getProperty(const QString &key) {
        //QNetworkAccessManager *nam = new QNetworkAccessManager(this);

        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QVariantList propertyList;
        QVariantMap property;
        QVariantMap action;
        QVariantMap map;
        QVariantMap prop;

        propertyList << key;
        action.insert("properties", propertyList);
        map.insert("jsonrpc", "2.0");
        map.insert("method", "Application.GetProperties");
        map.insert("params", action);
        map.insert("id", "1");

        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        QString dataStr = QString::fromLatin1(data);

        qDebug(data);
        QNetworkReply * reply = nam->post(request, data);
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        //connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(parseVolume(QNetworkReply*)));
        qDebug("jees");
        return 0;
    }

    Q_INVOKABLE void setVolume(const qint32 volume) {
        //QNetworkAccessManager *nam = new QNetworkAccessManager(this);


        QNetworkRequest request;
        request.setUrl(QUrl("http://" + addr + ":" + port + "/jsonrpc"));
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        //'{"jsonrpc": 2.0", "method": "Application.SetVolume", "params": { "value": ' +str(newvolume) + '}, "id": 1}'


        QVariantMap map;
        QVariantMap value;
        value.insert("volume", volume);
        map.insert("jsonrpc", "2.0");
        map.insert("method", "Application.Setvolume");
        map.insert("params", value);
        map.insert("id","1");
        QJson::Serializer serializer;
        QByteArray data = serializer.serialize(map);
        qDebug(data);
        QString dataStr = QString::fromLatin1(data);

        QNetworkReply * reply = nam->post(request, data);
        //connect(reply, SIGNAL(readyRead()),nam, SLOT(deleteLater()));
        //connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    }

    Q_INVOKABLE quint32 getVolume() {
        getProperty("volume");
        delay();
        //while (serverVolume == -1);
        return serverVolume;
    }

};

#endif // MAIN_H
