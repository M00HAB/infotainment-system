//https://www.figma.com/design/Ytk3WPtb3oO9QNKm0IwoXV/Steely-Wheels---tvOS-App-(Community)?node-id=22-190&t=8zStTzYABNmcMAeO-0
//https://www.figma.com/design/TnfgSUpsAM6lcpu1r5iuXm/Electric-Car-Console-UI-Design?node-id=1-2&t=hpdQh6sCITeI619F-0
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QCommandLineParser>
#include <QMimeType>
#include <qmediaformat.h>
#include <algorithm>
#include <SearchMedia.h>

using namespace Qt::Literals::StringLiterals;

struct NameFilters
{
    QStringList filters;
    int preferred = 0;
};

static NameFilters nameFilters()
{
    QStringList result;
    QString preferredFilter;
    const auto formats = QMediaFormat().supportedFileFormats(QMediaFormat::Decode);
    for (qsizetype m = 0, size = formats.size(); m < size; ++m) {
        const auto format = formats.at(m);
        QMediaFormat mediaFormat(format);
        const QMimeType mimeType = mediaFormat.mimeType();
        if (mimeType.isValid()) {
            QString filter = QMediaFormat::fileFormatDescription(format) + " ("_L1;
            const auto suffixes = mimeType.suffixes();
            for (qsizetype i = 0, size = suffixes.size(); i < size; ++i) {
                if (i)
                    filter += u' ';
                filter += "*."_L1 + suffixes.at(i);
            }
            filter += u')';
            result.append(filter);
            if (mimeType.name() == "video/mp4"_L1)
                preferredFilter = filter;
        }
    }
    std::sort(result.begin(), result.end());
    const int preferred = preferredFilter.isEmpty() ? 0 : int(result.indexOf(preferredFilter));
    return { result, preferred };
}

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QCoreApplication::setOrganizationDomain("Minya University");
    QCoreApplication::setOrganizationName("ODC");
    QCoreApplication::setApplicationName("EcoDrive");
    QCommandLineParser parser;

    QGuiApplication app(argc, argv);


    app.setWindowIcon(QIcon("qrc:/assets/techcoderhub_logo.jpg"));
    const QUrl style(QStringLiteral("qrc:/Style.qml"));
    qmlRegisterSingletonType(style, "Style", 1, 0, "Style");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));



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
