#ifndef THERMONATOR_GUI_WINDOWMANAGER_HPP
#define THERMONATOR_GUI_WINDOWMANAGER_HPP

#include <QObject>
#include <QString>
#include <QUrl>

namespace thermonator::gui {

class WindowManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QUrl currentPage READ currentPage NOTIFY currentPageChanged)
public:
    WindowManager(QObject *parent = nullptr);

    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) = delete;
    WindowManager(WindowManager &&) = delete;
    WindowManager &operator=(WindowManager &&) = delete;
    ~WindowManager() = default;

    QUrl currentPage();

    void setCurrentPage(const QUrl &currentPage);

public slots:
    void onLoadScanConnectPage();

    void onLoadThermostatConfigurationPage();

signals:
    void currentPageChanged();

private:
    QUrl mCurrentPage;
};

} // namespace thermonator::gui

Q_DECLARE_METATYPE(thermonator::gui::WindowManager *)

#endif
