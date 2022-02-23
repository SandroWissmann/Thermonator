
#include "backend/ConnectionHandler.hpp"
#include "backend/DeviceManager.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>

#include <memory>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    thermonator::ConnectionHandler connectionHandler;

    // thermonator::DeviceManager deviceManager;
    //  currently also connects to service and sends one command
    //  these actions should be later triggered depending on gui events
    // deviceManager.startScan();

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

/*

static const QString service1 = "{00001801-0000-1000-8000-00805f9b34fb}";
static const QString service2 = "{0000180a-0000-1000-8000-00805f9b34fb}";
static const QString service3 = "{3e135142-654f-9090-134a-a6ff5bb77046}";
static const QString service4 = "{9e5d1e47-5c13-43a0-8635-82ad38a1386f}";

void DeviceHandler::onServiceScanDone()
{
    qDebug() << "onServiceScanDone";

    if (mLowEnergyServicePtr) {
        mLowEnergyServicePtr.reset();
    }

    if (mService3Found) {
        auto lowEnergyServicePlainPtr =
            mLowEnergyControllerPtr->createServiceObject(
                QBluetoothUuid(service3), this);
        mLowEnergyServicePtr.reset(lowEnergyServicePlainPtr);
    }

    if (mLowEnergyServicePtr) {
        connect(mLowEnergyServicePtr.get(), &QLowEnergyService::stateChanged,
                this, &DeviceHandler::onServiceStateChanged);
        connect(mLowEnergyServicePtr.get(),
                &QLowEnergyService::characteristicWritten, this,
                &DeviceHandler::onServiceCharacteristicWrittenChanged);
        connect(mLowEnergyServicePtr.get(),
                &QLowEnergyService::characteristicRead, this,
                &DeviceHandler::onServiceCharacteristicReadChanged);
        connect(mLowEnergyServicePtr.get(),
                &QLowEnergyService::characteristicChanged, this,
                &DeviceHandler::onServiceCharacteristicChanged);
        connect(mLowEnergyServicePtr.get(),
                qOverload<QLowEnergyService::ServiceError>(
                    &QLowEnergyService::error),
                this, &DeviceHandler::onServiceErrorChanged);
        mLowEnergyServicePtr->discoverDetails();
    }
}

    if (deviceInfoPtr->address().toString() == "00:1A:22:16:BE:93") {
        onConnectToService("00:1A:22:16:BE:93");
    }

*/
