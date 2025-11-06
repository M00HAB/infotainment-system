#include "weathermanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

WeatherManager::WeatherManager(QObject *parent) : QObject(parent) ,m_Temp("100"){
    manager = new QNetworkAccessManager(this);
    apiKey = "a184ce8615b780c3576c6e19c59a9ae3";  // Replace with a valid OpenWeatherMap API key
    connect(manager, &QNetworkAccessManager::finished, this, &WeatherManager::onReplyFinished);
}

QString WeatherManager::Temp() const{
    return m_Temp;
}

QString  WeatherManager::setTemp(QString newTemp)
{
    if (m_Temp == newTemp)
        return newTemp;
    m_Temp = newTemp;
    emit tempChanged();
}

void WeatherManager::fetchWeather(const QString &city) {
    QString url = QString("http://api.openweathermap.org/data/2.5/weather?q=%1&appid=%2&units=metric")
    .arg(city)
        .arg(apiKey);

    QNetworkRequest request(QUrl(url));  // ✅ Correctly create the request object
    manager->get(QNetworkRequest(QUrl(url)));

    qDebug() << "Fetching weather from URL:" << url;
}

void WeatherManager::onReplyFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    qDebug() << "Raw API response:" << QString(responseData);

    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObject = jsonResponse.object();

    if (!jsonObject.contains("main") || !jsonObject.contains("weather")) {
        qDebug() << "Invalid JSON response.";
        reply->deleteLater();
        return;
    }

    double temp = jsonObject["main"].toObject()["temp"].toDouble();
    QString weatherCondition = jsonObject["weather"].toArray()[0].toObject()["main"].toString();
    int humidity = jsonObject["main"].toObject()["humidity"].toInt();
    double windSpeed = jsonObject["wind"].toObject()["speed"].toDouble();

    emit weatherUpdated(QString::number(temp, 'f', 1) + "°C",
                        weatherCondition,
                        QString::number(humidity) + "%",
                        QString::number(windSpeed, 'f', 1) + " m/s");

    reply->deleteLater();
}

