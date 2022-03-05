
#include "backend/ConnectionHandler.hpp"
//#include "backend/DeviceManager.hpp"
#include "backend/DeviceScanner.hpp"
#include "backend/gui/WindowManager.hpp"
#include "backend/gui/pages/scanConnectPage/ScanConnectPageController.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QLocale>
#include <QTranslator>

#include <memory>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    using namespace thermonator;

    ConnectionHandler connectionHandler;

    // DeviceManager deviceManager;
    //   currently also connects to service and sends one command
    //   these actions should be later triggered depending on gui events
    // deviceManager.startScan();

    gui::ScanConnectPageController scanConnectPageController;

    DeviceScanner deviceScanner;

    QObject::connect(&scanConnectPageController,
                     &gui::ScanConnectPageController::requestStartScanning,
                     &deviceScanner, &DeviceScanner::onStartScanning);

    QObject::connect(&deviceScanner, &DeviceScanner::deviceDiscovered,
                     &scanConnectPageController,
                     &gui::ScanConnectPageController::onReceiveNewDevice);

    gui::WindowManager windowManager;
    // keep in mind later that we also want to return to this page
    // then add additional signal / slot connection
    windowManager.onLoadScanConnectPage();

    QObject::connect(
        &scanConnectPageController,
        &gui::ScanConnectPageController::loadThermostatConfigurationPage,
        &windowManager, &gui::WindowManager::onLoadThermostatConfigurationPage);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Thermonator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;

    auto qmlContext = engine.rootContext();
    qmlContext->setContextProperty("scanConnectPageController",
                                   &scanConnectPageController);

    qmlContext->setContextProperty("windowManager", &windowManager);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
