#pragma once

#include "libopenshot/Qt/VideoRenderWidget.h"
#include <QMouseEvent>
#include <QtPlayer.h>

using namespace openshot;

class MyVideoWidget : public VideoRenderWidget {

    Q_OBJECT

private:
    QtPlayer *m_player;
    void PlayPause();

public:
    explicit MyVideoWidget(QWidget *parent = nullptr, QtPlayer *player = nullptr);
    void SetPlayer(QtPlayer *player);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
