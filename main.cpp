#include "editor.h"
#include <libopenshot/OpenShot.h>

using namespace std;
using namespace openshot;

void setHardwareAccel() {
    Settings::Instance()->HARDWARE_DECODER = 1;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    setHardwareAccel();

    Editor editor;

    editor.resize(800, 600);
    editor.setWindowTitle("SVEditor");
    editor.show();
    //editor.playPause();

    return QApplication::exec();
}
