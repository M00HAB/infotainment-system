#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QGeoCoordinate>

class LocationManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QGeoCoordinate currentLocation READ currentLocation NOTIFY locationChanged)

public:
    explicit LocationManager(QObject *parent = nullptr);
    QGeoCoordinate currentLocation() const { return m_currentLocation; }

signals:
    void locationChanged();

private slots:
    void updateLocation(const QGeoPositionInfo &info);

private:
    QGeoPositionInfoSource *m_locationSource;
    QGeoCoordinate m_currentLocation;
};

#endif // LOCATIONMANAGER_H
