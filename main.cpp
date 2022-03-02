
#include "backend/ConnectionHandler.hpp"
//#include "backend/DeviceManager.hpp"
#include "backend/DeviceScanner.hpp"
#include "backend/gui/scanConnectWindow/ScanConnectWindowController.hpp"
#include "backend/gui/scanConnectWindow/ScannedDevicesModel.hpp"

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

    gui::ScanConnectWindowController scanConnectWindowController;
    gui::ScannedDevicesModel scannedDevicesModel;

    DeviceScanner deviceScanner;

    QObject::connect(&scanConnectWindowController,
                     &gui::ScanConnectWindowController::requestStartScanning,
                     &scannedDevicesModel,
                     &gui::ScannedDevicesModel::onResetDevices);

    QObject::connect(&scanConnectWindowController,
                     &gui::ScanConnectWindowController::requestStartScanning,
                     &deviceScanner, &DeviceScanner::onStartScanning);

    QObject::connect(&deviceScanner, &DeviceScanner::deviceDiscovered,
                     &scannedDevicesModel,
                     &gui::ScannedDevicesModel::onAddDevice);

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
    qmlContext->setContextProperty("scanConnectWindowController",
                                   &scanConnectWindowController);

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
