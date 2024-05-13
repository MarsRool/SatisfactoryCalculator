#include <QApplication>
#include <QTranslator>
#include <QQmlApplicationEngine>
#include "DataModel/Theme.h"
#include "Helpers/logger.h"
#include "ViewModel/MainVM.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setApplicationName("SatisfactoryCalculator");
    app.setOrganizationName("MarsGames");

    try
    {
        Logger* logger = Logger::getInstance();
        Q_UNUSED(logger)
        qDebug() << "main: starting app";
    } catch (...) {}

    auto model = std::make_unique<MainVM>(engine);
    qmlRegisterType<MainVM>("Factory", 1, 0, "MainModel");
    qmlRegisterType<ThemeWrapper>("Factory", 1, 0, "Theme");
    qmlRegisterType<OptionsVM>("Factory", 1, 0, "Options");

    const QUrl url(QStringLiteral("qrc:/View/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url, &model](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
            {
                qDebug() << "main: cannot find url";
                QGuiApplication::exit(-1);
            }
            obj->setProperty("mainModel", QVariant::fromValue(model.get()));
            qDebug() << "main: qml engine started";
        }, Qt::QueuedConnection);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
