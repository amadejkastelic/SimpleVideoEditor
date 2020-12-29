#include "editor.h"
#include <thread>
#include <libopenshot/OpenShot.h>
#include <QApplication>

using namespace std;
using namespace openshot;

void setHardwareAccel(QSettings *settings) {
    Settings::Instance()->HARDWARE_DECODER = settings->value("video/hw_acceleration", 0).toInt();
    Settings::Instance()->OMP_THREADS = std::thread::hardware_concurrency();
    Settings::Instance()->HIGH_QUALITY_SCALING = true;
    Settings::Instance()->FF_THREADS = std::thread::hardware_concurrency();
    Settings::Instance()->DE_LIMIT_HEIGHT_MAX = 10000;
    Settings::Instance()->DE_LIMIT_WIDTH_MAX = 10000;
    Settings::Instance()->WAIT_FOR_VIDEO_PROCESSING_TASK = false;

    if (Settings::Instance()->HARDWARE_DECODER != 0) {
        cerr << "Hardware decoding enabled... Detected thread count: " << Settings::Instance()->FF_THREADS << endl;
    }
}

int main(int argv, char **args) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argv, args);

    QCoreApplication::setOrganizationName("AK");
    QCoreApplication::setApplicationName("SVEditor");

    QSettings settings;
    settings.setValue("app/name", "SVEditor");
    settings.sync();
    //QQuickStyle::setStyle("Material");

    setHardwareAccel(&settings);

    Editor editor;
    editor.resize(1280, 720);
    editor.setWindowTitle(QObject::tr("SVEditor"));
    editor.show();
    //editor.playPause();

    return QApplication::exec();
}
