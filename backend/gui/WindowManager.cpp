#include "WindowManager.hpp"

namespace thermonator::gui {

WindowManager::WindowManager(QObject *parent) : QObject{parent}
{
    qRegisterMetaType<thermonator::gui::WindowManager *>();
}

QUrl WindowManager::currentPage()
{
    return mCurrentPage;
}

void WindowManager::setCurrentPage(const QUrl &currentPage)
{
    if (mCurrentPage == currentPage) {
        return;
    }
    mCurrentPage = currentPage;
    emit currentPageChanged();
}

void WindowManager::onLoadScanConnectPage()
{
    QUrl ScanConnectPageUrl{"pages/ScanConnectPage.qml"};
    setCurrentPage(ScanConnectPageUrl);
}

} // namespace thermonator::gui
