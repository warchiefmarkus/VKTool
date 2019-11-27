#include <connection/apimethodexecutor.h>
#include <connection/customnetworkmanager.h>
#include <QUrl>
#include <QDebug>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>

ApiMethodExecutor::ApiMethodExecutor(QString token, QObject* parent) :
    QObject(parent),
    token(token),
    timeoutCounter(0)
{
    networkAccessManager = new CustomNetworkAccessManager(QSsl::TlsV1SslV3, QSslSocket::VerifyNone, this);
    cache = new QNetworkDiskCache(this);
    cache->setMaximumCacheSize(500*1024*1024); // 500 Mb
    cache->setCacheDirectory("cacheDir");
    networkAccessManager->setCache(cache);
}

ApiMethodExecutor::ApiMethodExecutor(QObject* parent) :
    QObject(parent),
    timeoutCounter(0)
{
    networkAccessManager = new CustomNetworkAccessManager(QSsl::TlsV1SslV3, QSslSocket::VerifyNone, this);
    cache = new QNetworkDiskCache(this);
    cache->setMaximumCacheSize(500*1024*1024); // 500 Mb
    cache->setCacheDirectory("cacheDir");
    networkAccessManager->setCache(cache);
}

QJsonObject ApiMethodExecutor::executeMethod(const QString& methodName, const QMap<QString, QString>& params) const {
    QString urlStr = "https://api.vk.com/method/" + methodName + "?";
    foreach (QString paramName, params.keys()) {
        urlStr.append(paramName).append("=").append(params.value(paramName)).append("&");
    }
    urlStr.append("v=5.00&");
    urlStr.append("https=1&");
    urlStr.append("access_token=").append(token);
    qDebug() <<  "API method executing:" << methodName << "URL STR" << urlStr;
    QUrl url = QUrl(urlStr);
    QNetworkRequest request = QNetworkRequest(url);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    request.setAttribute(QNetworkRequest::CacheSaveControlAttribute, true); // CACHE
    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QByteArray buffer;
    QNetworkReply* reply = networkAccessManager->post(request,buffer);
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
                this, SLOT(updateDownloadProgress(qint64, qint64)));

    QEventLoop eventLoop;

    networkAccessManager->connect(reply,SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec();
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        QString responseJsonStr = QString::fromUtf8(reply->readAll());
        QJsonDocument document = QJsonDocument::fromJson(responseJsonStr.toUtf8());
        emit networkStatus(true);
        return document.object();
    } else {
        qDebug() << "API Method execute: Network Error:" << reply->errorString();
        emit networkStatus(false);
        return executeMethod(methodName,params);
    }
}

QJsonObject ApiMethodExecutor::get(QUrl url)
{
    qDebug() <<  "get method executing";
    QNetworkRequest request = QNetworkRequest(url);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    request.setAttribute(QNetworkRequest::CacheSaveControlAttribute, true);
    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply = networkAccessManager->get(request);
    QEventLoop eventLoop;

    networkAccessManager->connect(reply,SIGNAL(finished()),&eventLoop, SLOT(quit()));
    eventLoop.exec(QEventLoop::AllEvents);
    reply->deleteLater();
    if (reply->error() == QNetworkReply::NoError) {
        qDebug () << " TEST GET ";
        qDebug () << reply->readAll();
        QString responseJsonStr = QString::fromUtf8(reply->readAll());
        QJsonDocument document = QJsonDocument::fromJson(responseJsonStr.toUtf8());
        emit networkStatus(true);
        return document.object();
    } else {
        qDebug() << "API Method get: Network Error:" << reply->errorString();
        emit networkStatus(false);
        return get(url);
    }
}

ApiMethodExecutor::~ApiMethodExecutor() {
    delete networkAccessManager;
    token.clear();
}

void ApiMethodExecutor::updateDownloadProgress(qint64 bR, qint64 bT)
{
    qDebug() << " reply progress: "  << (bR/1024) << "kb total " << (bT/1024);
}
