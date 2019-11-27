#include <connection/customnetworkmanager.h>
#include <QSslConfiguration>
#include <QNetworkRequest>
#include <QSsl>
#include <QNetworkDiskCache>


CustomNetworkAccessManager::CustomNetworkAccessManager (QSsl::SslProtocol protocol, QSslSocket::PeerVerifyMode mode, QObject* parent) : QNetworkAccessManager(parent) {
    this->protocol = protocol;
    this->mode = mode;
}

QNetworkReply * CustomNetworkAccessManager::createRequest (Operation op, const QNetworkRequest& req, QIODevice* outgoingData ) {
    QSslConfiguration config = req.sslConfiguration();
    config.setPeerVerifyMode(mode);
    config.setProtocol(protocol);
    QNetworkRequest request(req);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
    request.setSslConfiguration(config);
    return QNetworkAccessManager::createRequest(op, request, outgoingData);
}
