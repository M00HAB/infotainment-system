#ifndef WEATHERMANAGER_H
#define WEATHERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class WeatherManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString Temp READ Temp WRITE setTemp NOTIFY tempChanged )

public:
    explicit WeatherManager(QObject *parent = nullptr);
    void fetchWeather(const QString &city);
    QString Temp() const;

public slots:
    QString setTemp(QString newTemp);

signals:
    void weatherUpdated(const QString &temperature, const QString &condition, const QString &humidity, const QString &windSpeed);
    void tempChanged();

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:

    QNetworkAccessManager *manager;
    QString apiKey;
    QString m_Temp;
};



#endif // WEATHERMANAGER_H
