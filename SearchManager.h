#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QGeoCoordinate>

class SearchManager : public QObject {
    Q_OBJECT
public:
    explicit SearchManager(QObject *parent = nullptr);

    // Function to search for an address using OpenStreetMap API
    void searchAddress(const QString &query);

signals:
    // Emit signal when an address is found (lat, lon)
    void addressFound(QGeoCoordinate coordinate);

private slots:
    // Handles API response
    void handleSearchResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager m_networkManager;
};

#endif // SEARCHMANAGER_H
