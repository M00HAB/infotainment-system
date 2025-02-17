#include "LocationManager.h"
#include <QDebug>

LocationManager::LocationManager(QObject *parent) : QObject(parent) {
    m_locationSource = QGeoPositionInfoSource::createDefaultSource(this);
    if (m_locationSource) {
        connect(m_locationSource, &QGeoPositionInfoSource::positionUpdated, this, &LocationManager::updateLocation);
        m_locationSource->startUpdates();
    } else {
        qDebug() << "No valid GPS source found!";
    }
}

void LocationManager::updateLocation(const QGeoPositionInfo &info) {
    m_currentLocation = info.coordinate();
    emit locationChanged();
}
