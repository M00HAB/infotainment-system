#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include <QQmlContext>
#include <weathermanager.h>
#include <MusicPlayer.h>



int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationDomain("techcoderhub.com");
    QCoreApplication::setOrganizationName("TechCoderHub");
    QCoreApplication::setApplicationName("Raemon");

    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("qrc:/assets/techcoderhub_logo.jpg"));
    const QUrl style(QStringLiteral("qrc:/Style.qml"));
    qmlRegisterSingletonType(style, "Style", 1, 0, "Style");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    MusicPlayer musicPlayer;
    engine.rootContext()->setContextProperty("musicPlayer", &musicPlayer);

    WeatherManager weather;


    engine.rootContext()->setContextProperty("weatherManager", &weather);


    QObject::connect(&weather, &WeatherManager::weatherUpdated,
                     [](const QString &temp, const QString &condition, const QString &humidity, const QString &windSpeed) {
                         qDebug() << "Temperature:" << temp;
                         qDebug() << "Condition:" << condition;
                         qDebug() << "Humidity:" << humidity;
                         qDebug() << "Wind Speed:" << windSpeed;
                     });

    weather.fetchWeather("Cairo");
    weather.fetchWeather("Cairo");


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);



    return app.exec();
}
