#pragma once

#include <QString>
#include <QStringList>

class Lists {

public:
    static QStringList variables() {
        return {"variables", "part", "path", "start", "end", "type", "audio", "text", "value", "position", "size",
                "font", "color", "scale", "animation", "length"};
    }

    static QStringList position() {
        return {"bottom", "top", "left", "right"};
    }

    static QStringList type() {
        return {"image", "video", "text"};
    }

    static QStringList scale() {
        return {"fit", "crop", "scale", "none"};
    }

};
