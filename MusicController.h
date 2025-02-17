#ifndef MUSICCONTROLLER_H
#define MUSICCONTROLLER_H

#include <QObject>

class MusicController : public QObject {
    Q_OBJECT
    Q_PROPERTY(double currentFMStation READ currentFMStation WRITE setCurrentFMStation NOTIFY currentFMStationChanged)
    Q_PROPERTY(QString connectedDeviceName READ connectedDeviceName WRITE setConnectedDeviceName NOTIFY connectedDeviceNameChanged)
    Q_PROPERTY(bool spotifyConnected READ spotifyConnected WRITE setSpotifyConnected NOTIFY spotifyConnectedChanged)
public:
    explicit MusicController(QObject *parent = nullptr)
        : QObject(parent), m_currentFMStation(93.3), m_connectedDeviceName(""), m_spotifyConnected(false) {}

    double currentFMStation() const { return m_currentFMStation; }
    void setCurrentFMStation(double station) {
        if (qFuzzyCompare(m_currentFMStation, station))
            return;
        m_currentFMStation = station;
        emit currentFMStationChanged();
    }

    QString connectedDeviceName() const { return m_connectedDeviceName; }
    void setConnectedDeviceName(const QString &name) {
        if (m_connectedDeviceName == name)
            return;
        m_connectedDeviceName = name;
        emit connectedDeviceNameChanged();
    }

    bool spotifyConnected() const { return m_spotifyConnected; }
    void setSpotifyConnected(bool connected) {
        if (m_spotifyConnected == connected)
            return;
        m_spotifyConnected = connected;
        emit spotifyConnectedChanged();
    }

signals:
    void currentFMStationChanged();
    void connectedDeviceNameChanged();
    void spotifyConnectedChanged();

private:
    double m_currentFMStation;
    QString m_connectedDeviceName;
    bool m_spotifyConnected;
};

#endif // MUSICCONTROLLER_H
