#ifndef APIMETHODEXECUTOR_H
#define APIMETHODEXECUTOR_H

#include <QObject>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QNetworkAccessManager>
#include <connection/customnetworkmanager.h>
#include <QNetworkDiskCache>

class ApiMethodExecutor : public QObject {
    Q_OBJECT

public:
    ApiMethodExecutor(QString token, QObject* parent = 0);
    ApiMethodExecutor(QObject* parent = 0);
    QJsonObject executeMethod(const QString& methodName, const QMap<QString,QString>& params) const;
    QJsonObject get(QUrl url);
    void setToken(QString tok){ this->token = tok; }
    ~ApiMethodExecutor();
    //QNetworkAccessManager* networkAccessManager;
signals:
    void networkStatus(bool isOk) const;
private:
    QNetworkDiskCache* cache;
    CustomNetworkAccessManager* networkAccessManager;
    QString token;
    volatile unsigned int timeoutCounter;
private slots:
    void updateDownloadProgress(qint64, qint64);
};
#endif // APIMETHODEXECUTOR_H

