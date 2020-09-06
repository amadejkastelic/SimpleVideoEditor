#include "editor.h"
#include <libopenshot/OpenShot.h>

using namespace std;
using namespace openshot;

void setHardwareAccel() {
    Settings::Instance()->HARDWARE_DECODER = 1;
    Settings::Instance()->OMP_THREADS = 24;
    Settings::Instance()->HIGH_QUALITY_SCALING = true;
    Settings::Instance()->FF_THREADS = 24;
    Settings::Instance()->DE_LIMIT_HEIGHT_MAX = 10000;
    Settings::Instance()->DE_LIMIT_WIDTH_MAX = 10000;
    Settings::Instance()->WAIT_FOR_VIDEO_PROCESSING_TASK = true;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("AK");
    QCoreApplication::setApplicationName("SVEditor");

    setHardwareAccel();

    Editor editor;
    editor.resize(800, 600);
    editor.setWindowTitle("SVEditor");
    editor.show();
    //editor.playPause();

    return QApplication::exec();
}
