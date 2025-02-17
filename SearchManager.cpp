#include "SearchManager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

SearchManager::SearchManager(QObject *parent) : QObject(parent), m_networkManager(this) {}

void SearchManager::searchAddress(const QString &query) {
    // ✅ Correct URL for searching an external location
    QString url = "https://nominatim.openstreetmap.org/search?q=" + query + "&format=json";

    // ✅ Make sure request does NOT use device GPS
    QNetworkRequest request{QUrl(url)};
    request.setHeader(QNetworkRequest::UserAgentHeader, "QtLocation");

    QNetworkReply *reply = m_networkManager.get(request);
    connect(reply, &QNetworkReply::finished, this, [=]() { handleSearchResponse(reply); });

    qDebug() << "Sent request to: " << url;
}

void SearchManager::handleSearchResponse(QNetworkReply *reply) {
    if (!reply->error()) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
        QJsonArray results = jsonResponse.array();

        if (!results.isEmpty()) {
            QJsonObject firstResult = results.first().toObject();
            double lat = firstResult["lat"].toString().toDouble();
            double lon = firstResult["lon"].toString().toDouble();
            emit addressFound(QGeoCoordinate(lat, lon));
        }
    } else {
        qDebug() << "Network error:" << reply->errorString();
    }
    reply->deleteLater();
}
