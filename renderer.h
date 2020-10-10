#pragma once

#include "data/files.h"
#include <QtPlayer.h>
#include <QtTextReader.h>
#include <libopenshot/OpenShot.h>
#include <QFontDatabase>

using namespace std;
using namespace openshot;

class Renderer {

public:
    static uint render(const vector<spv::File *> &files, Timeline *timeline);
};
