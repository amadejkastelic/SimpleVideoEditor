#pragma once

#include "video_render_widget.h"
#include <QMouseEvent>
#include <QtPlayer.h>
#include <QTimer>

using namespace openshot;

class MyVideoWidget : public VideoRenderWidget {

    Q_OBJECT

private:
    QtPlayer *m_player;
    QTimer *m_timer;
    void PlayPause();

public:
    explicit MyVideoWidget(QWidget *parent = nullptr, QtPlayer *player = nullptr, QTimer *timer = nullptr);
    void SetPlayer(QtPlayer *player);
    void SetTimer(QTimer *timer);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
